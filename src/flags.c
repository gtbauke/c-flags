#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/flags.h"

static flag_context global_flags_context = {0};

static flag_definition *find_flag_definition(const char *flag_name) {
  size_t len = strlen(flag_name);

  for (size_t i = 0; i < global_flags_context.flags_count; i++) {
    if (strncmp(flag_name, global_flags_context.definitions[i].name, len) == 0) {
      return &global_flags_context.definitions[i];
    }
  }

  return NULL;
}

bool is_flag(const char *argument) {
  return strncmp(argument, FLAG_PREFIX, FLAG_PREFIX_LENGTH) == 0;
}

void parse_flags(int argc, char *argv[]) {
  for (int i = 0; i < argc; i++) {
    if (is_flag(argv[i])) {
      char *flag_name = argv[i] + FLAG_PREFIX_LENGTH;
      flag_definition *flag_definition = find_flag_definition(flag_name);

      if (flag_definition == NULL) {
        fprintf(stderr, "Unknown flag: %s\n", flag_name);
        exit(1);
      }

      switch (flag_definition->type) {
        case FLAG_TYPE_STRING: {
          if (i + 1 >= argc) {
            fprintf(stderr, "Missing value for flag: %s\n", flag_name);
            exit(1);
          }

          char *value = argv[i + 1];
          flag_definition->value.as_string = value;
          i++;
        } break;
        case FLAG_TYPE_INTEGER: {
          if (i + 1 >= argc) {
            fprintf(stderr, "Missing value for flag: %s\n", flag_name);
            exit(1);
          }

          char *value = argv[i + 1];
          flag_definition->value.as_uint64t = atoi(value);
          i++;
        } break;
        case FLAG_TYPE_FLOAT: {
          if (i + 1 >= argc) {
            fprintf(stderr, "Missing value for flag: %s\n", flag_name);
            exit(1);
          }

          char *value = argv[i + 1];
          flag_definition->value.as_double = atof(value);
          i++;
        } break;
        case FLAG_TYPE_BOOLEAN: {
          flag_definition->value.as_boolean = true;
        } break;
        default:
          break;
      }
    }
  }
}

static flag_definition *define_flag(char *flag_name, char *flag_description, flag_type flag_type) {
  if (global_flags_context.flags_count >= MAX_FLAGS) {
    fprintf(stderr, "Too many flags defined\n");
    exit(1);
  }

  flag_definition *flag = &global_flags_context.definitions[global_flags_context.flags_count++];
  memset(flag, 0, sizeof(flag_definition*));

  flag->name = flag_name;
  flag->description = flag_description;
  flag->type = flag_type;

  return flag;
}

char **define_string_flag(char *flag_name, char *flag_description, char *default_value) {
  flag_definition *flag = define_flag(flag_name, flag_description, FLAG_TYPE_STRING);
  flag->value.as_string = default_value;
  flag->default_value.as_string = default_value;

  return &flag->value.as_string;
}

uint64_t *define_integer_flag(char *flag_name, char *flag_description, uint64_t default_value) {
  flag_definition *flag = define_flag(flag_name, flag_description, FLAG_TYPE_INTEGER);
  flag->value.as_uint64t = default_value;
  flag->default_value.as_uint64t = default_value;

  return &flag->value.as_uint64t;
}

double *define_double_flag(char *flag_name, char *flag_description, double default_value) {
  flag_definition *flag = define_flag(flag_name, flag_description, FLAG_TYPE_FLOAT);
  flag->value.as_double = default_value;
  flag->default_value.as_double = default_value;

  return &flag->value.as_double;
}

bool *define_boolean_flag(char *flag_name, char *flag_description, bool default_value) {
  flag_definition *flag = define_flag(flag_name, flag_description, FLAG_TYPE_BOOLEAN);
  flag->value.as_boolean = default_value;
  flag->default_value.as_boolean = default_value;

  return &flag->value.as_boolean;
}
