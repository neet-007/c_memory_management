void swap_strings(char **a, char **b) {
  char *temp_address = *a;
  *a = *b;
  *b = temp_address;
}
