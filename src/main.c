#include <stdio.h>

[[nodiscard("Please evaluate return value!")]]
int f_nodiscard(unsigned int a, unsigned int b)
{
    return a + b;
}

int main(void)
{
    printf("C standard %ld\n", __STDC_VERSION__);
    printf("gcc version %d.%d.%d\n", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__ );

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

