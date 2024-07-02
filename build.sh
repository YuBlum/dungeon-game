CC="bear -- cc"
FLAGS="-Wall -Wextra -Werror -g"
SRCS="src/main.c"
INCS="-I src/"
LIBS="-lGL -lglfw -lm"
OUT="-o game"

$CC $FLAGS $SRCS $INCS $LIBS $OUT
