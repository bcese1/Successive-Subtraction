//******************************************************************************
// Name: Benjamin Cesero
// Date Due: 9/26/22
// Course: ELEC3371
// Description:
// The program is used to divde two bytes by successive subtraction.
// The quotient is then displayed on LEDs on PORTD/L in binary.
// The remainder bits are reversed back to the inital value.
//******************************************************************************

//******************************************************************************
//Global Variables
unsigned long int numer = 10;
unsigned long int dem = 2;

void main()
{
//******************************************************************************
//Assembly
asm{

    MOVW R0, #LO_ADDR(RCC_APB2ENR+0) // Load the lower two bytes of R0 and RCC
    MOVT R0, #HI_ADDR(RCC_APB2ENR+0) // Load the higher two bytes of R0 and RCC
    LDR R1, [R0]                     // Load the content from R0 to R1

    MOV R2, #0x00000020              // Set bit 5 of R2 to 1 in hex
    ORRS R1, R1, R2                  // Write a 1 in bit 5 of R1
    STR R1, [R0]                     // Store the result of the previous opp

    MOV R3, #0x33333333              // Save value of GPIO_CRL/H in R3
    MOVW R0, #LO_ADDR(GPIOD_CRL+0)   // Load the lower two bytes of R0 and GPIO_D
    MOVT R0, #HI_ADDR(GPIOD_CRL+0)   // Load the higher two bytes of R0 and GPIO_D
    STR R3, [R0]                     // Store the result of the previous opp

    MOVW R0, #LO_ADDR(_numer+0)      // Load the lower two bytes of R0 and numer
    MOVT R0, #HI_ADDR(_numer+0)      // Load the higher two bytes of R0 and numer
    LDR R1, [R0]                     // Loads the value of R0 in R1

    MOVW R0, #LO_ADDR(_dem+0)        // Load the lower two bytes of R0 and dem
    MOVT R0, #HI_ADDR(_dem+0)        // Load the higher two bytes of R0 and dem
    LDR R2, [R0]                     // Loads the value of R0 in R2
    ADD R4, #1                       // Sets R4(Counter) to 1

    REPEAT:                          // Loops Begins
      SUBS R1, R2                    // R1 - R2 = R1, Checks for zero flag
      CMP R1, #0                     // Compares the value of R1 to 0
      BLE THE_END                    // If CMP is greater or equal then JMP
      ADD R4, #1                     // Add 1 to R4 for each loop
      BNE REPEAT                     // Go back to Repeat
    THE_END:                         // Branch for LEDS
      MOVW R0, #LO_ADDR(GPIOD_ODR+0) // Load the lower two bytes of R0 and GPIO_D
      MOVT R0, #HI_ADDR(GPIOD_ODR+0) // Load the higher two bytes of R0 and GPIO_D
      STR R4, [R0]                   // Store the result of the previous opp
      MUL R1, R4, R2                 // R4*R2=R1 Reverse bits back to inital val

}



}