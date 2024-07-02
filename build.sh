CC="bear -- cc"
FLAGS="-Wall -Wextra -Werror -g"
VENDOR="vendor/glad/src/glad.c"
SRCS="src/main.c src/window.c src/renderer.c"
INCS="-I src/ -I vendor/glad/include/"
LIBS="-lGL -lglfw -lm"
OUT="-o game"

$CC $FLAGS $VENDOR $SRCS $INCS $LIBS $OUT
