#include <stdlib.h>
#include <string.h>

void swap(void *vp1, void *vp2, size_t size) {
  void *temp_buff = malloc(size);

  if (temp_buff == (void *)0){
    return;
  }

  memcpy(temp_buff, vp1, size);
  memcpy(vp1, vp2, size);
  memcpy(vp2, temp_buff, size);

  free(temp_buff);
}
