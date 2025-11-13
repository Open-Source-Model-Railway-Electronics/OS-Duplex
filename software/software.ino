#include "src/macros.h"
#include "src/ST.h"
#include "src/NmraDcc.h"

const int dipSwitches[] = {1,2,3,4,5} ;
const int nDipSwitches = sizeof(  dipSwitches ) / sizeof ( dipSwitches[0] ) ;

NmraDcc     dcc ;

const int   nOutputs = 4 ;
Timer       pulseTimer[nOutputs] ;
Timer       signalTimer ;
const int   pins[nOutputs] = {6,7,8,9} ;

uint8_t     state[nOutputs] = { 0, 0, 0, 0 } ;

const int   Pulse       = 0 ;
const int   Steady      = 1 ;
const int   Double      = 0 ;
const int   Single      = 1 ;

bool        bGettingAddress ;

typedef struct Settings_
{
    uint16_t    primaryAddress ;
    uint16_t    secondaryAddress ;
    uint8_t     single_double       : 1 ;
    uint8_t     pulse_steady        : 1 ;
    uint8_t     slaved              : 1 ;
    uint8_t     isSignal           : 1 ;

} Settings ;

Settings output[2] ;

uint16_t beginAddress = 50 ;

uint8_t newValue = ;

void readDipswitches()
{
    static uint8_t  oldValue = 0xFF ;
    newValue = 0 ;

    for( int i = 0 ; i < nDipSwitches ; i ++ ) 
    {
        pinMode( dipSwitches[i], INPUT_PULLUP ) ;
        newValue |= ( digitalRead( dipSwitches[i] ) << i ) ;
    }

    if( newValue != oldValue )
    {   oldValue  = newValue ;
        
        // number1 
        // number2
        // output[0].settings.bits.single_double      = (newValue >> 0) & 1 ;
        // output[0].settings.bits.pulse_continous    = (newValue >> 1) & 1 ;
        // output[1].settings.bits.single_double      = (newValue >> 2) & 1 ;
        // output[1].settings.bits.pulse_continous    = (newValue >> 3) & 1 ;
        // output[1].settings.bits.slaved             = (newValue >> 4) & 1 ;

        calculateAddresses() ;
    }
}


extern uint16_t beginAddress ;

void calculateAddresses()
{
    // reset
    output[0].primaryAddress   = 0 ;
    output[0].secondaryAddress = 0 ;
    output[1].primaryAddress   = 0 ;
    output[1].secondaryAddress = 0 ;

    uint16_t addr = beginAddress ;

    switch( newValue & 0b11111 )
    {
        // ─────────────── S = 0 (no slave)
        case 0b10100:                               // single pulse    single pulse    S=0
        case 0b10110:                               // single pulse    single steady   S=0
        case 0b11100:                               // single steady   single pulse    S=0
        case 0b11110:                               // single steady   single steady   S=0
            // out1 single (2), out2 single (2)
            output[0].primaryAddress   = addr++ ;
            output[0].secondaryAddress = addr++ ;
            output[1].primaryAddress   = addr++ ;
            output[1].secondaryAddress = addr++ ;
            break ;

        // out1 single (2), out2 double (1)  → 3 adressen totaal
        case 0b10000:                               // single pulse    double pulse    S=0
        case 0b10010:                               // single pulse    double steady   S=0
        case 0b11000:                               // single steady   double pulse    S=0
        case 0b11010:                               // single steady   double steady   S=0
            output[0].primaryAddress   = addr++ ;
            output[0].secondaryAddress = addr++ ;
            output[1].primaryAddress   = addr++ ;
            break ;

        // out1 double (1), out2 single (2)  → 3 adressen totaal
        case 0b00100:                               // double pulse    single pulse    S=0
        case 0b00110:                               // double pulse    single steady   S=0
        case 0b01100:                               // double steady   single pulse    S=0
        case 0b01110:                               // double steady   single steady   S=0
            output[0].primaryAddress   = addr++ ;
            output[1].primaryAddress   = addr++ ;
            output[1].secondaryAddress = addr++ ;
            break ;

        // beide double (1+1)  → 2 adressen totaal
        case 0b00000:                               // double pulse    double pulse    S=0
        case 0b00010:                               // double pulse    double steady   S=0
        case 0b01000:                               // double steady   double pulse    S=0
        case 0b01010:                               // double steady   double steady   S=0
            output[0].primaryAddress   = addr++ ;
            output[1].primaryAddress   = addr++ ;
            break ;

        // ─────────────── S = 1 (slave-varianten met extra vrij relais) → 2 adressen totaal
        // (out1 double 1 adres + vrij relais 1 adres)
        case 0b00101:                               // double pulse    slave single    S=1
        case 0b01101:                               // double steady   slave single    S=1
            output[0].primaryAddress     = addr++ ;
            output[1].secondaryAddress   = addr++ ;
            break ;

        // ─────────────── S = 1 (signal / fully slaved) → 1 logisch adres
        case 0b00001:                               // double pulse    slave double    S=1
        case 0b00011:                               // double pulse    slave double    S=1
        case 0b00111:                               // double pulse    slave single    S=1
        case 0b01001:                               // double steady   slave double    S=1
        case 0b01011:                               // double steady   slave double    S=1
        case 0b01111:                               // double steady   slave single    S=1
        default: 
            output[0].primaryAddress   = addr++ ;
            break ;
    }

    //if

}


/* if output is steady, needs to be turned ON, so we need to store 4 states of 4 possible outputs.
   if output is slaved, the relay need to turned on or off
*/
void initalizeOutputs() 
{
}


void setup()
{
    for( int i = 0 ; i < nOutputs ; i ++ )
    {
        pulseTimer[i].set( TIMER_ON, 75 ) ;
    }

    Serial.begin( 115200 ) ;

    dcc.pin( 2, 0 ) ;
    dcc.init( MAN_ID_DIY, 11, FLAGS_OUTPUT_ADDRESS_MODE | FLAGS_DCC_ACCESSORY_DECODER, 0 );

    signalTimer.set( TIMER_TOGGLE, 333 ) ;
    initalizeOutputs() ;
}

void loop()
{
    readDipswitches() ;

    dcc.process() ;

    updatePulses() ;

    handleElektroFrog() ;

    handleSignal() ;
}

uint8_t aspectMask ;
uint8_t blinkMask ;

void notifyDccSigOutputState( uint16_t address, uint8_t aspect ) // incomming DCC EXT commands
{
    if( address != beginAddress ) return ;

    if( output[0].isSignal )
    {
        aspectMask   =  aspect & 0x0F ;
        blinkMask    = (aspect >> 4) & 0x0F ;
    }
}

void handleSignal() // todo for later
{
    signalTimer.update( 1 ) ;

    if( signalTimer.Q )
    {
        for( int i = 0 ; i < nOutputs ; i ++ )
        {
            const uint8_t bit = (uint8_t)(1u << i) ;
            
            if( (blinkMask & bit) != 0u ) { digitalWrite( pins[i], !  digitalRead( pins[i] )) ; }
            else                          { digitalWrite( pins[i], !!(aspectMask & bit     )) ; }
        }
    }
}

static uint8_t pointDirection ;
static uint8_t      frogState = 0 ;
void setElektroFrog( uint8_t direction )
{
    pointDirection = direction ;
    frogState = 1 ;
}

// handles both relay in combination with the pulse outpus.
void handleElektroFrog()
{
    static Timer frogTimer ;
    frogTimer.update() ;

    switch( frogState )
    {
    case 0: // idle
        
        break ;

    case 1:
        digitalWrite( pins[2], LOW ) ; // kill both array
        digitalWrite( pins[3], LOW ) ;
        frogTimer.set( TIMER_ON, 25 ) ;
        frogState ++ ;
        break ;

    case 2:
        if( frogTimer.Q )
        {
            if( pointDirection ) state[1] = 1 ; // fire up the pulse.
            else                 state[0] = 1 ; 

            frogTimer.update( 0 ) ;             // clear timer
            frogTimer.set( TIMER_ON, 100 ) ;    // reset timer
            frogState ++ ;
        }
        break ;

    case 3:
        if( frogTimer.Q )
        {
            if( pointDirection ) digitalWrite( pins[3], HIGH ) ;
            else                 digitalWrite( pins[2], HIGH ) ;
            frogState = 0 ;
        }

        break ;
    }
}

void notifyDccAccTurnoutOutput( uint16_t address, uint8_t direction, uint8_t output_ ) // incomming DCC commands
{
    if( bGettingAddress ) 
    {
        if( direction > 0 ) direction = 1 ; 
        beginAddress = address ;
        calculateAddresses() ;
        return ;
    }

    // if( mode == signal
    // ||  mode == complexPoint ) return ;

    if( direction > 0 ) direction = 1 ; 

    for( int i = 0 ; i < 2 ; i ++ ) 
    {
        if( address == output[i].primaryAddress )
        {
            if( output[i].pulse_steady == Steady )
            {
                digitalWrite( pins[i*2], direction ) ;       // happens for both single and double steady

                if( output[i].single_double == Double )    // when we are double we also inverse control the other output
                {
                    digitalWrite( pins[i*2+1], !direction ) ;
                }
                return ;
            }

            if( output[i].pulse_steady  ==  Pulse 
            &&  output[i].single_double == Double )       // we are both pulsed and double (single pulsed is not used)
            {
                if( i == 0 && output[1].slaved )
                {
                    setElektroFrog( direction ) ;
                    return ;
                }

                if( direction == 0 ) state[i*2  ] = 1 ;     // mark the pin to be pulsed 
                else                 state[i*2+1] = 1 ;     // mark the other pin to be pulsed 
                return ;
            }
        }
        if( address == output[i].secondaryAddress         // we only have a secondary address if we are a single output
        &&  output[i].pulse_steady == Steady )            // and we are not pulsed!, we dont do single pulse
        {
            digitalWrite( pins[i*2+1], direction ) ;
            return ;
        }
    }
}


void updatePulses()
{
    static int8_t  activePulse = -1;                 // -1 = none

    for( int i = 0 ; i < nOutputs ; i ++ ) 
    if( state[i] && activePulse < 0 )
    {
        digitalWrite( pins[i], HIGH );
        pulseTimer[i].IN = 1 ;
        activePulse = i;
        break;
    }
        

    if( activePulse >= 0 
    &&  pulseTimer[activePulse].update( 1 ) )
    {
        digitalWrite( pins[activePulse], LOW );
        state[activePulse] = 0;
        pulseTimer[activePulse].update( 0 );
        activePulse = -1;
    }
}
