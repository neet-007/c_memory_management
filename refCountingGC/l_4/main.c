#include "assert.h"
#include <stdio.h>
#include <stdlib.h>

#include "include/bootlib.h"
#include "include/munit.h"
#include "include/snekobject.h"

void test_vector3_refcounting(const MunitParameter params[], void* data) {
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

void test_vector3_refcounting_same(const MunitParameter params[], void* data) {
    snek_object_t *foo = new_snek_integer(1);

    snek_object_t *vec = new_snek_vector3(foo, foo, foo);
    assert_int(foo->refcount, ==, 4, "foo is now referenced by vec x3");

    refcount_dec(foo);
    assert(!boot_is_freed(foo));

    refcount_dec(vec);
    assert(boot_is_freed(foo));
    assert(boot_is_freed(vec));
    assert(boot_all_freed());
}

void test_int_has_refcount(const MunitParameter params[], void* data) {
    snek_object_t *obj = new_snek_integer(10);
    assert_int(obj->refcount, ==, 1, "Refcount should be 1 on creation");
    free(obj);
}

void test_inc_refcount(const MunitParameter params[], void* data) {
    snek_object_t *obj = new_snek_float(4.20);
    assert_int(obj->refcount, ==, 1, "Refcount should be 1 on creation");

    refcount_inc(obj);
    assert_int(obj->refcount, ==, 2, "Refcount should be incremented");

    free(obj);
}

void test_dec_refcount(const MunitParameter params[], void* data) {
    snek_object_t *obj = new_snek_float(4.20);

    refcount_inc(obj);
    assert_int(obj->refcount, ==, 2, "Refcount should be incremented");

    refcount_dec(obj);
    assert_int(obj->refcount, ==, 1, "Refcount should be decremented");

    assert(!boot_is_freed(obj));

    free(obj);
}

void test_refcount_free_is_called(const MunitParameter params[], void* data) {
    snek_object_t *obj = new_snek_float(4.20);

    refcount_inc(obj);
    assert_int(obj->refcount, ==, 2, "Refcount should be incremented");

    refcount_dec(obj);
    assert_int(obj->refcount, ==, 1, "Refcount should be decremented");

    refcount_dec(obj);
    assert(boot_is_freed(obj));
    assert(boot_all_freed());
}

void test_allocated_string_is_freed(const MunitParameter params[], void* data) {
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

int main(int argc, char* argv[]) {
    MunitTest tests[] = {
        { "/vector3", test_vector3_refcounting, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
        { "/vector3-same", test_vector3_refcounting_same, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
        { "/has_refcount", test_int_has_refcount, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
        { "/inc_refcount", test_inc_refcount, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
        { "/dec_refcount", test_dec_refcount, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
        { "/free_refcount", test_refcount_free_is_called, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
        { "/string_freed", test_allocated_string_is_freed, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
        { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
    };

    MunitSuite suite = {
        "refcount", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
    };

    return munit_suite_main(&suite, NULL, argc, argv);
}
