#include "include/exercise.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Helper function for assertion to avoid using macros
void assert_not_null(void *ptr, const char *message) {
    if (ptr == NULL) {
        fprintf(stderr, "%s\n", message);
        exit(EXIT_FAILURE);
    }
}

void assert_string_equal(const char *str1, const char *str2, const char *message) {
    if (strcmp(str1, str2) != 0) {
        fprintf(stderr, "%s\nExpected: %s, Got: %s\n", message, str2, str1);
        exit(EXIT_FAILURE);
    }
}

void assert_int(int actual, int expected, const char *message) {
    if (actual != expected) {
        fprintf(stderr, "%s\nExpected: %d, Got: %d\n", message, expected, actual);
        exit(EXIT_FAILURE);
    }
}

void assert_ptr_not_equal(void *ptr1, void *ptr2, const char *message) {
    if (ptr1 == ptr2) {
        fprintf(stderr, "%s\nPointers should not be equal\n", message);
        exit(EXIT_FAILURE);
    }
}

// Test function for creating a token pointer array with a single token
void test_create_token_pointer_array_single() {
    token_t token = {"hello", 1, 1};
    token_t **result = create_token_pointer_array(&token, 1);

    assert_not_null(result, "Result array should not be null");
    assert_not_null(result[0], "First token pointer should not be null");
    assert_string_equal(result[0]->literal, "hello", "Literal should match");
    assert_int(result[0]->line, 1, "Line number should match");
    assert_int(result[0]->column, 1, "Column number should match");
    assert_ptr_not_equal(result[0], &token, "Token pointer should not point to original token");

    free(result[0]);
    free(result);
}

// Test function for creating a token pointer array with multiple tokens
void test_create_token_pointer_array_multiple() {
    token_t tokens[3] = {
        {"foo", 1, 1},
        {"bar", 2, 5},
        {"baz", 3, 10}
    };
    token_t **result = create_token_pointer_array(tokens, 3);

    assert_not_null(result, "Result array should not be null");
    for (int i = 0; i < 3; i++) {
        assert_not_null(result[i], "Token pointer should not be null");
        assert_string_equal(result[i]->literal, tokens[i].literal, "Literal should match");
        assert_int(result[i]->line, tokens[i].line, "Line number should match");
        assert_int(result[i]->column, tokens[i].column, "Column number should match");
        assert_ptr_not_equal(result[i], &tokens[i], "Token pointer should not point to original token");
    }

    for (int i = 0; i < 3; i++) {
        free(result[i]);
    }
    free(result);
}

// Test function for checking memory allocation in creating a token pointer array
void test_create_token_pointer_array_memory_allocation() {
    token_t tokens[2] = {
        {"test1", 1, 1},
        {"test2", 2, 2}
    };
    token_t **result = create_token_pointer_array(tokens, 2);

    assert_not_null(result, "Result array should not be null");
    assert_not_null(result[0], "First token pointer should not be null");
    assert_not_null(result[1], "Second token pointer should not be null");
    assert_ptr_not_equal(result[0], result[1], "Token pointers should be different");
    assert_ptr_not_equal(result[0], &tokens[0], "First token pointer should not point to original token");
    assert_ptr_not_equal(result[1], &tokens[1], "Second token pointer should not point to original token");

    free(result[0]);
    free(result[1]);
    free(result);
}

// Main function to run the tests
int main() {
    // Run the tests
    test_create_token_pointer_array_single();
    test_create_token_pointer_array_multiple();
    test_create_token_pointer_array_memory_allocation();

    printf("All tests passed successfully!\n");
    return 0;
}
