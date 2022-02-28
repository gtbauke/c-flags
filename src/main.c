#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/flags.h"

typedef char* c_string;

int main(int argc, char *argv[]) {
  c_string *title_flag = define_string_flag("title", "Title of the todo", NULL);
  c_string *description_flag = define_string_flag("description", "Description of the todo", "This is a default description");

  uint64_t *priority_flag = define_integer_flag("priority", "Priority of the todo", 0);
  double *progress_flag = define_double_flag("progress", "Progress of the todo", 0.0);
  bool *completed_flag = define_boolean_flag("completed", "Whether the todo is completed", false);

  parse_flags(argc, argv++);

  printf("Title: %s\n", *title_flag);
  printf("Description: %s\n", *description_flag);
  printf("Priority: %llu\n", *priority_flag);
  printf("Progress: %f\n", *progress_flag);
  printf("Completed: %s\n", *completed_flag ? "true" : "false");

  return 0;
}
