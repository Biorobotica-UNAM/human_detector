# ID único asignado por el tracker
int32 id

# Posición en el espacio (u, v en imagen o x, y, z si ya es 3D)
float64[] position

# Velocidad estimada [vx, vy]
float64[] velocity

# Si el track está confirmado o es una detección nueva
bool is_confirmed

# (Opcional) Si decides volver a usar esqueletos en el futuro
float32[] keypoints

