/* ========================================
 *
 * main.c (for Calc_Final_Proj/SPIS_to_Arduino)
  2.4.16 by Rod......ver. 1 (slight edits and clean up)

  The following SPI portions of code copied/edited from "SPI_Design01_kit_030"
  
    1. This is a SPIS-only design (within PSoC 3), to interface to an Arduino SPIM
	2. In addition, all the variables for the final calculator design are provided
 *
 * ========================================
*/
/*******************************************************************************
* The following description is from the original SPIM + SPIS design, but here it
*   has been edited to be a SPIS only design
*
* Description:
*  This is source code for example project of the SPI
*  (Master, Slave) components.
*  Parameters used:
*   Mode                0(CPHA ==0, CPOL ==0)                
*   Data lines          MOSI+MISO
*   Shift direction     MSB First
*   DataBits:           8 
*   Bit Rate            1Mbit/s
*   Clock source        External 
*
*  SPI communication test using software buffer. 8 bytes are transmitted
*  between SPI Master and SPI Slave.
*  Received data are displayed on LCD. 
*/

#include <device.h>

/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*  Main function performs following functions:
*   1. Declares variables.
*   2. Enables interrupts.
*   3. Starts all used components.
*   4. Waits for the Slave's SPI Done state generation.
*   5. Displays SPI Slave received data.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
// variables needed for the final calculator design + clock
int sec = 0;
int min = 0;

char plus = '+';
char sub = '-';
char muli = 'x';
char div = '/';
char equal = '=';
char key;

int op1Done = 0;
int lcd_pointer = 1;

int opChooser = 0;
int opReset = 0;

int numTemp = 0;
int num1 = 0;
int num2 = 0;
int numRemainder = 0;
int numResult = 0;

int calcReset = 0;


int main()
{    
    /* Software buffers use internal interrupt functionality to interact with
    * hardware buffers. Thus global interrupt enable command should be called 
    */
    CyGlobalIntEnable;
    
    /* We need to start Character LCD and Slave components */
    LCD_Start();
    SPIS_Start();
    Timer_1_Start();
    TimerISR_Start();
    //LCD_Position(0,0);
    //LCD_PrintString("Type Num");
        
    // Continuously loop to receive/print keyboard data from Ardo-SPIM to PSoC3-SPIS
    while(1)
    {
        // Wait for received data ready
        while(!(SPIS_ReadRxStatus() & SPIS_STS_RX_FIFO_NOT_EMPTY));
                
        // Read from SPIS Rx software buffer      
		// store received data
		key = SPIS_ReadRxData();
			
		// Print key data to LCD screen, as hex value to show ASCII code
		//LCD_Position(1,6);
        //LCD_PrintHexUint8(key);
		
		// Subtract ASCII 30 to allow actual digit value to display
		//key = key - '0';
		numTemp = key - 30;
        
        if(key == '#' && calcReset == 1)
            {
                int sec = 0;
                int min = 0;
                int op1Done = 0;
                int lcd_pointer = 1;
                int opChooser = 0;
                int opReset = 0;
                int numTemp = 0;
                int num1 = 0;
                int num2 = 0;
                int numRemainder = 0;
                int numResult = 0;
                int calcReset = 0;
                
                LCD_Position(0,0);
                LCD_PrintString("Type Num");
            }
            
        if (key == '*' & opChooser < 5 & calcReset == 0)
            {
                LCD_Position(0,0);
                LCD_PrintString("");
                
            }
        
		LCD_Position(1,12);		
		LCD_PrintNumber(numTemp);
	//Numbers	
	else if (key == '0-9' && calcReset == 0)
	   {
		op1Done = 0;
		LCD_PrintString("Oprtn w/ *");
		/*Process first operand*/ (num1);
		LCD_Position()
		
	   }
	}
   }
}

/* [] END OF FILE */

