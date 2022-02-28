#ifndef todo_flags_h
#define todo_flags_h

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_FLAGS 32
#define FLAG_PREFIX "--"
#define FLAG_PREFIX_LENGTH 2

typedef enum {
  FLAG_TYPE_STRING,
  FLAG_TYPE_BOOLEAN,
  FLAG_TYPE_FLOAT,
  FLAG_TYPE_INTEGER,
} flag_type;

typedef union {
  char *as_string;
  bool as_boolean;
  double as_double;
  uint64_t as_uint64t;
} flag_value;

typedef struct {
  flag_type type;

  char *name;
  char *description;

  flag_value value;
  flag_value default_value;
} flag_definition;

typedef struct {
  flag_definition definitions[MAX_FLAGS];
  size_t flags_count;
} flag_context;

bool is_flag(const char *argument);
void parse_flags(int argc, char *argv[]);

char **define_string_flag(char *flag_name, char *flag_description, char *default_value);
uint64_t *define_integer_flag(char *flag_name, char *flag_description, uint64_t default_value);
double *define_double_flag(char *flag_name, char *flag_description, double default_value);
bool *define_boolean_flag(char *flag_name, char *flag_description, bool default_value);

#endif
