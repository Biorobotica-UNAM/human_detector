import rclpy
from rclpy.node import Node
import numpy as np
from scipy.optimize import linear_sum_assignment

from std_msgs.msg import Header
from human_interfaces.msg import PersonTracks, PersonTrack  # opcional si ya tienes .msg

# -----------------------------
# CONFIGURACIÓN
# -----------------------------

MAX_TRACK_AGE = 10        # frames sin ver → eliminar
MATCH_THRESHOLD = 0.65    # umbral para considerar que dos personas son la misma


# -----------------------------
# HELPERS
# -----------------------------

def normalize_descriptor(kp):
    """
    Construye un descriptor robusto usando solo keypoints visibles.
    kp: array shape (17,3)
    """
    # keypoints relevantes desde atrás: shoulders, hips
    S_L = kp[5]   # left shoulder
    S_R = kp[6]   # right shoulder
    H_L = kp[11]  # left hip
    H_R = kp[12]  # right hip

    desc = []

    def dist(a, b):
        if a[2] < 0.1 or b[2] < 0.1:
            return None
        return np.linalg.norm(a[:2] - b[:2])

    # Distancias base
    d_shoulder = dist(S_L, S_R)
    d_hip      = dist(H_L, H_R)
    d_torso_L  = dist(S_L, H_L)
    d_torso_R  = dist(S_R, H_R)

    base = np.mean([d for d in [d_shoulder, d_hip, d_torso_L, d_torso_R] if d is not None])

    if base is None:
        return None  # no se puede construir descriptor

    # descriptor normalizado
    for d in [d_shoulder, d_hip, d_torso_L, d_torso_R]:
        desc.append(d / base if d is not None else 0.0)

    return np.array(desc, dtype=np.float32)



# -----------------------------
# TRACK CLASS
# -----------------------------

class Track:
    def __init__(self, track_id, keypoints, descriptor):
        self.id = track_id
        self.kp = keypoints
        self.desc = descriptor
        self.age = 0

    def update(self, keypoints, descriptor):
        self.kp = keypoints
        self.desc = descriptor
        self.age = 0

    def step(self):
        self.age += 1



# -----------------------------
# PERSON TRACKER NODE
# -----------------------------

class PersonTrackerNode(Node):

    def __init__(self):
        super().__init__('person_tracker')

        # Suscriptor al tópico de keypoints del YOLO pose
        self.sub_kp = self.create_subscription(
            PersonTracks,
            '/human_detection/keypoints',
            self.keypoints_callback,
            10
        )

        # Publicador de tracks con IDs estables
        self.pub_tracks = self.create_publisher(
            PersonTracks,
            '/human_detection/person_tracks',
            10
        )

        self.tracks = []
        self.next_id = 0

        self.get_logger().info("Person Tracker iniciado con Hungarian Algorithm")



    # ---------------
    # CALLBACK
    # ---------------
    def keypoints_callback(self, msg):
        detections = msg.persons   # lista de PersonTrack-like con keypoints

        # Convertir detecciones a arrays
        kp_list = []
        desc_list = []

        for det in detections:
            kp = np.array(det.keypoints, dtype=np.float32).reshape(17,3)
            desc = normalize_descriptor(kp)
            if desc is None:
                continue
            kp_list.append(kp)
            desc_list.append(desc)

        if len(desc_list) == 0:
            self._step_tracks()
            return

        # ---------------
        # Matching (Hungarian)
        # ---------------

        if len(self.tracks) == 0:
            # crear tracks nuevos
            for i in range(len(kp_list)):
                self._new_track(kp_list[i], desc_list[i])
            self._publish_tracks()
            return

        # matriz de costos: tracks_prev vs detecciones_nuevas
        cost = np.zeros((len(self.tracks), len(desc_list)))

        for i, tr in enumerate(self.tracks):
            for j, desc in enumerate(desc_list):
                cost[i, j] = np.linalg.norm(tr.desc - desc)

        row_ind, col_ind = linear_sum_assignment(cost)

        assigned_tracks = set()
        assigned_dets = set()

        # aplicar matches
        for r, c in zip(row_ind, col_ind):

            if cost[r, c] < MATCH_THRESHOLD:
                # match válido
                self.tracks[r].update(kp_list[c], desc_list[c])
                assigned_tracks.add(r)
                assigned_dets.add(c)

        # crear tracks nuevos para detecciones sin match
        for j in range(len(kp_list)):
            if j not in assigned_dets:
                self._new_track(kp_list[j], desc_list[j])

        # incrementar edad de tracks no asignados
        self._step_tracks()

        # publicar
        self._publish_tracks()



    # ------------------
    # TRACK HELPERS
    # ------------------

    def _new_track(self, kp, desc):
        tr = Track(self.next_id, kp, desc)
        self.tracks.append(tr)
        self.next_id += 1

    def _step_tracks(self):
        # incremente edad y remueve tracks viejos
        alive_tracks = []
        for tr in self.tracks:
            tr.step()
            if tr.age <= MAX_TRACK_AGE:
                alive_tracks.append(tr)
        self.tracks = alive_tracks

    def _publish_tracks(self):
        msg = PersonTracks()
        msg.header = Header()
        msg.header.stamp = self.get_clock().now().to_msg()

        for tr in self.tracks:
            pt = PersonTrack()
            pt.id = tr.id
            pt.keypoints = tr.kp.flatten().tolist()
            pt.confidence = 1.0 - min(1.0, np.mean(tr.desc))  # placeholder
            msg.persons.append(pt)

        self.pub_tracks.publish(msg)



def main(args=None):
    rclpy.init(args=args)
    node = PersonTrackerNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    node.destroy_node()



if __name__ == '__main__':
    main()
