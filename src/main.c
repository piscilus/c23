#include <stdio.h>
#include <uchar.h> /* char8_t */

[[nodiscard("Please evaluate return value!")]]
int f_nodiscard(unsigned int a, unsigned int b)
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

int main(void)
{
    printf("C standard %ld\n", __STDC_VERSION__);
    printf("gcc version %d.%d.%d\n", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__ );

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

    /* Digit separators
     */
    unsigned int n1 = 0xDEAD'BEEF;
    unsigned int n2 = 123'456'789;
    float f1 = 0.123'45F;
    float f2 = 12'345.6F;

    /* Binary integer constants
     * https://en.cppreference.com/w/c/language/integer_constant
     */
    unsigned int m = 0b10101010;

    /* Warning directive
     * https://en.cppreference.com/w/c/preprocessor/error
     */
    #warning "Finally a warning directive besides error."

    /* Attribute
     * [[nodiscard]]
     * [[nodiscard("reason")]]
     */
    printf("%i\n", __has_c_attribute(nodiscard));
    f_nodiscard(n1, n2); // implicit discard -> warning
    (void) f_nodiscard(n1, n2); // explicit discard -> okay

    return 0;
}

