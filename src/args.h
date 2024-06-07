
typedef struct {
  bool help;
  bool list;
  char* system;
} Args;

Args* parse_args(int argc, char **argv);
