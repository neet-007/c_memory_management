#include "assert.h"
#include <stdlib.h>

#include "include/bootlib.h"
#include "include/snekobject.h"

void test_array_set() {
    snek_object_t *foo = new_snek_integer(1);

    snek_object_t *array = new_snek_array(1);
    snek_array_set(array, 0, foo);
    assert_int(foo->refcount, ==, 2, "foo is now referenced by array");

    assert(!boot_is_freed(foo));

    refcount_dec(foo);
    refcount_dec(array);
    assert(boot_all_freed());
}

void test_array_free() {
    snek_object_t *foo = new_snek_integer(1);
    snek_object_t *bar = new_snek_integer(2);
    snek_object_t *baz = new_snek_integer(3);

    snek_object_t *array = new_snek_array(2);
    snek_array_set(array, 0, foo);
    snek_array_set(array, 1, bar);
    assert_int(foo->refcount, ==, 2, "foo is now referenced by array");
    assert_int(bar->refcount, ==, 2, "bar is now referenced by array");
    assert_int(baz->refcount, ==, 1, "baz is not yet referenced by array");

    refcount_dec(foo);
    assert(!boot_is_freed(foo));

    snek_array_set(array, 0, baz);
    assert(boot_is_freed(foo));

    refcount_dec(bar);
    refcount_dec(baz);
    refcount_dec(array);
    assert(boot_all_freed());
}

void test_vector3_refcounting() {
    snek_object_t *foo = new_snek_integer(1);
    snek_object_t *bar = new_snek_integer(2);
    snek_object_t *baz = new_snek_integer(3);

    snek_object_t *vec = new_snek_vector3(foo, bar, baz);
    assert_int(foo->refcount, ==, 2, "foo is now referenced by vec");
    assert_int(bar->refcount, ==, 2, "bar is now referenced by vec");
    assert_int(baz->refcount, ==, 2, "baz is now referenced by vec");

    refcount_dec(foo);
    assert(!boot_is_freed(foo));

    refcount_dec(vec);
    assert(boot_is_freed(foo));

    assert(!boot_is_freed(bar));
    assert(!boot_is_freed(baz));

    refcount_dec(bar);
    refcount_dec(baz);

    assert(boot_all_freed());
}

void test_int_has_refcount() {
    snek_object_t *obj = new_snek_integer(10);
    assert_int(obj->refcount, ==, 1, "Refcount should be 1 on creation");

    free(obj);
}

void test_inc_refcount() {
    snek_object_t *obj = new_snek_float(4.20);
    assert_int(obj->refcount, ==, 1, "Refcount should be 1 on creation");

    refcount_inc(obj);
    assert_int(obj->refcount, ==, 2, "Refcount should be incremented");

    free(obj);
}

void test_dec_refcount() {
    snek_object_t *obj = new_snek_float(4.20);

    refcount_inc(obj);
    assert_int(obj->refcount, ==, 2, "Refcount should be incremented");

    refcount_dec(obj);
    assert_int(obj->refcount, ==, 1, "Refcount should be decremented");

    assert(!boot_is_freed(obj));

    free(obj);
}

void test_refcount_free_is_called() {
    snek_object_t *obj = new_snek_float(4.20);

    refcount_inc(obj);
    assert_int(obj->refcount, ==, 2, "Refcount should be incremented");

    refcount_dec(obj);
    assert_int(obj->refcount, ==, 1, "Refcount should be decremented");

    refcount_dec(obj);
    assert(boot_is_freed(obj));
    assert(boot_all_freed());
}

void test_allocated_string_is_freed() {
    snek_object_t *obj = new_snek_string("Hello @wagslane!");

    refcount_inc(obj);
    assert_int(obj->refcount, ==, 2, "Refcount should be incremented");

    refcount_dec(obj);
    assert_int(obj->refcount, ==, 1, "Refcount should be decremented");
    assert_string_equal(obj->data.v_string, "Hello @wagslane!", "references str");

    refcount_dec(obj);
    assert(boot_is_freed(obj));
    assert(boot_all_freed());
}

int main() {
    test_array_set();
    test_array_free();
    test_int_has_refcount();
    test_inc_refcount();
    test_dec_refcount();
    test_refcount_free_is_called();
    test_allocated_string_is_freed();
    test_vector3_refcounting();

    return 0;
}
