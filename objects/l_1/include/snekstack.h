typedef enum SnekLangObjectKind {
  INTEGER
} snek_object_kind_t;

typedef union SnekLangObjectData {
  int v_int;
} snek_object_data_t;

typedef struct SnekLangObject {
  snek_object_kind_t kind;
  snek_object_data_t data;
} snek_object_t;
