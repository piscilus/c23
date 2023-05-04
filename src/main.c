#include <assert.h>
#include <stddef.h> /* unreachable */
#include <stdint.h>
#include <stdio.h>
#include <uchar.h> /* char8_t */

/* Attributes
 * [[nodiscard]]
 * [[maybe_unused]]
 * warning for unused parameter c suppressed by attribute, but not for d:
 * -> warning: unused parameter ‘d’ [-Wunused-parameter]
 */
[[nodiscard("Please evaluate return value!")]]
int f_nodiscard(unsigned int a, unsigned int b, [[maybe_unused]] int c, int d)
{
    return a + b;
}

typedef enum
{
    MODE_A,
    MODE_B,
    MODE_C,
    MODE_ERR
} mode_t;

/* Attribute
 * [[fallthrough]]
 */
int f_fallthrough(mode_t x)
{
    int r;

    switch (x)
    {
        case MODE_A:
            r = 42;
            break;
        case MODE_B:
            r = 12; /* warning: this statement may fall through [-Wimplicit-fallthrough] */
        case MODE_C:
            r = 69;
            break;
        case MODE_ERR:
        [[fallthrough]]; /* no warning because intentional fallthrough */
        default:
            r = 0;
            break;
    }

    return r;
}

int f_unreachable(mode_t x)
{
    int r;

    switch (x)
    {
        case MODE_A:
            r = 42;
            break;
        case MODE_B:
            r = 12;
            break;
        case MODE_C:
            r = 69;
            break;
        case MODE_ERR:
            r = 1;
            break;
        default: /* all possible cases handled before */
            assert(0);
            unreachable();
            break;
    }

    return r;
}


int main(void)
{
    printf("C standard %ld\n", __STDC_VERSION__);
    printf("gcc version %d.%d.%d\n", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__ );

    /* constexpr
     */
    const int8_t a = 5;
    constexpr int8_t b = 5;

    int8_t v, w;
    v = INT8_MAX + a; /* no warning */
    w = INT8_MAX + b; /* warning: overflow in conversion from ‘int’ to ‘int8_t’ {aka ‘signed char’} changes value from ‘132’ to ‘-124’ [-Woverflow] */

#if 0 /* to let the code compile */
    static_assert(a == 5); /* error: expression in static assertion is not constant */
#endif
    static_assert(b == 5); /* ok */

    /* u8 character constant for use with UTF-8 string literals
     *
     * U+006A   j   6a              LATIN SMALL LETTER J
     * U+00DF   ß   c3 9f           LATIN SMALL LETTER SHARP S
     * U+221B   ∛   e2 88 9b        CUBE ROOT
     * U+1F375  🍵  f0 9f 8d b5     TEACUP WITHOUT HANDLE
     *
     * (https://www.utf8-chartable.de/)
     */
    char8_t str[] = u8"jß∛🍵"; /* = "\U006a\U00df\U221B\U0001F375" */
    printf("u8 string: %s\n", str);
    for (size_t s = 0U; s < sizeof(str) / sizeof(str[0]); s++)
    {
        printf("%02X ", str[s]);
    }
    putchar('\n');

    /* static assert, a.k.a compile time assert
     * example to test implementation-defined size_t
     * compile time error: static assertion failed: "size_t must be 4!"
     */
    static_assert(8 == sizeof(size_t)); /* error on 32-bit machine */
    static_assert(8 == sizeof(size_t), "size_t must be 8!"); /* + optional message */
#if 0 /* to let the code compile on 64-bit machine */
    static_assert(4 == sizeof(size_t)); /* error on 64-bit machine */
    static_assert(4 == sizeof(size_t), "size_t must be 4!"); /* + optional message */
#endif

    /* predefined true and false (without stdbool.h)
     */
    [[maybe_unused]] _Bool x = true;
    [[maybe_unused]] _Bool y = false;

    /* Digit separators
     */
    unsigned int n1 = 0xDEAD'BEEF;
    unsigned int n2 = 123'456'789;
    [[maybe_unused]] float f1 = 0.123'45F;
    [[maybe_unused]] float f2 = 12'345.6F;

    /* Binary integer constants
     * https://en.cppreference.com/w/c/language/integer_constant
     */
    [[maybe_unused]] unsigned int m = 0b10101010;

    /* Warning directive
     * https://en.cppreference.com/w/c/preprocessor/error
     */
    #warning "Finally a warning directive besides error."

    /* Attribute
     * [[nodiscard]]
     * [[nodiscard("reason")]]
     */
    printf("%i\n", __has_c_attribute(nodiscard));
    f_nodiscard(n1, n2, 42, 69); // implicit discard -> warning
    (void) f_nodiscard(n1, n2, 42, 69); // explicit discard -> okay

    while(1);
    return 0;
}

