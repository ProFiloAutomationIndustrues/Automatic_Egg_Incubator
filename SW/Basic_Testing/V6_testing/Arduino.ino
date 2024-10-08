/*
  Set the DIP switch to Mode 1 (SW3 and SW4 are On )with power removed. Restore power and upload the Arduino Sketch “ArduinoESPCommunication
  Remove power and set the DIP switch to Mode 2 (SW5, SW6, SW7 are On)
  Change Arduino IDE to ESP8266 programming mode and upload the sketch “ESPRecieveCommunication”
  Remove power and set the dip switch to Mode 4 (SW1 and SW2 are On)
  Restore power
  Pressing the push button will cause the ATMega328 built in LED to flash and the LED connected to the ESP8266 will come on.
  Pressing the push button again will flash the built in LED and turn off the LED connected to the ESP8266

 Arduino UNO modalità programmazione: Arduino Uno normale Mode 1 (SW3 and SW4 are On )
 Arduino UNO modalità funzionamento + comunicazione seriale con ESP8266: Arduino Uno normale Mode 4 (SW1 and SW2 are On)

 https://lastminuteengineers.com/multiple-ds18b20-arduino-tutorial/ reading temperature by address
*/

/*
08/09 TO DO: - collegare ventolina ausiliaria sul PIN 3
              - testare che ora vada sempre e solo il riscaldatore ausiliario PIN 11
*/
/* LIBRARIES */
#include <SoftwareSerial.h>
#include <avr/wdt.h>
#include <ProfiloLibrary.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>
#include <Wire.h>
#include <RTClib.h>


/* PIN ARDUINO */
#define MAIN_HEATER_PIN 12
#define AUX_HEATER_PIN 11
#define UPPER_FAN_PIN 10
#define LOWER_FAN_PIN 9
#define STEPPPER_MOTOR_STEP_PIN 8
#define STEPPPER_MOTOR_DIRECTION_PIN 7
#define STEPPPER_MOTOR_MS1_PIN 6 
#define STEPPPER_MOTOR_MS2_PIN 5
#define STEPPPER_MOTOR_MS3_PIN 4
#define COOLING_EMERGENCY_FAN_PIN 3
#define CYCLE_TOGGLE_ANALOG0_PIN 14

#define LEFT_INDUCTOR_PIN 6
#define RIGHT_INDUCTOR_PIN 5
#define DHTPIN 4   //Pin a cui è connesso il sensore
#define ONE_WIRE_BUS 2

// A4 and A5 used for RTC module

#define SERIAL_SPEED 19200 
#define WATCHDOG_ENABLE false
#define DEFAULT_DEBOUNCE_TIME 25 //ms
#define ENABLE_SERIAL_PRINT_TO_ESP8266 true
#define ENABLE_SERIAL_PRINT_DEBUG false

/* TEMPERATURES SECTION */
#define SINGLE_SMALL_HEATER_PRESENT true // true = versione due con solo ventola e riscaldatore ausiliario da 100W. false = versione vecchia con riscaldatore ausiliario e principale


// ricorda di mettere una alimentazione forte e indipendente per i sensori. Ha migliorato molto la stabilità della lettura.
OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

#define MAX_REACHABLE_TEMPERATURE_SATURATION 40.0
#define TEMPERATURE_PRECISION 9 // DS18B20 digital termometer provides 9-bit to 12-bit Celsius temperature measurements
#define MAX_SENSORS 10
DeviceAddress Thermometer[MAX_SENSORS];
byte numberOfDevices;
byte Limit;
unsigned long conversionTime_DS18B20_sensors; // in millis
unsigned long lastTempRequest;

#if !defined(DEVICE_DISCONNECTED)
#define DEVICE_DISCONNECTED -127
#endif

temperatureController temperatureController;

bool automaticControl_var = true; //di default partiamo con controllo automatico a true

float higherHysteresisLimit, lowerHysteresisLimit;

bool mainHeater_var = false;
bool auxHeater_var = false;
bool upperFan_var = false;
bool lowerFan_var = false;

bool tooHighTemperature = false;


float temperatures[3]; // declaring it here, once I know the dimension
int temperatureControlModality = 1; // default TEMPERATURE CONTROL MODALITY 1: actualTemperature = maxValue

DeviceAddress tempDeviceAddress; // We'll use this variable to store a found device address

// Define a char array to store the hexadecimal representation of the address
char addressCharArray[17]; // 16 characters for the address + 1 for null terminator

char comparisonAddress[] = "28FF888230180179"; // indirizzo del sensore di temperatura che uso per fare HUMIDITY

byte controlTemperatureIndex; // i sensori di temperatura sono 4, ma quelli effettivi per il controllo della T sono 3. Uno è per l'umidità. Serve un indice separato.

bool mainHeaterSelected = true;
float temperature_heater_selection_lower_treshold, temperature_heater_selection_upper_treshold;

trigger mainHeaterSeleted_trigger; // rising/falling edge di quando dobbiamo usare il riscaldatore principale
trigger temperatureController_outputState_trigger; // rising/falling edge di quando dobbiamo scaldare o no. Ogni volta che cambia, mettiamo un delay per essere sicuri di non fare accendi/spegni con mal-letture dei sensori
/* END TEMPERATURES SECTION */

/* DHT22 HUMIDITY SENSOR */
#define DHTTYPE DHT22   //Tipo di sensore che stiamo utilizzando (DHT22)
DHT dht(DHTPIN, DHTTYPE); //Inizializza oggetto chiamato "dht", parametri: pin a cui è connesso il sensore, tipo di dht 11/22


int chk;
float humidity_fromDHT22;  //Variabile in cui verrà inserita la % di umidità
float temp_fromDHT22; //Variabile in cui verrà inserita la temperatura

float humiditySensor_temperature; // variabile buffer in cui, durante la lettura dei sensori DS18B20, metto quella del bulbo umido
float temperatureMeanValue; // temperatura media dell'incubatrice calcolata dall'oggetto temperatureController
float wetTermometer_fromDS18B20; // temperatura = humiditySensor_temperature che uso in sezione umidità del programma
/* END DHT22 HUMIDITY SENSOR */


/* MOTORS SECTION */
#define STEPPER_MOTOR_SPEED_DEFAULT 5 //rpm  opportuno stare sotto i 30rpm, perché il tempo ciclo di arduino prende un po' troppo.

float stepper_motor_speed = STEPPER_MOTOR_SPEED_DEFAULT;

stepperMotor eggsTurnerStepperMotor(STEPPPER_MOTOR_STEP_PIN, STEPPPER_MOTOR_DIRECTION_PIN, STEPPPER_MOTOR_MS1_PIN, STEPPPER_MOTOR_MS2_PIN, STEPPPER_MOTOR_MS3_PIN, 1.8);

bool move = false;
bool direction = false; 

bool stepperAutomaticControl_var = true; // parto di default a true con il girauova

antiDebounceInput leftInductor_input(LEFT_INDUCTOR_PIN, DEFAULT_DEBOUNCE_TIME);
antiDebounceInput rightInductor_input(RIGHT_INDUCTOR_PIN, DEFAULT_DEBOUNCE_TIME);

// variabile per manual control
bool stepperMotor_moveForward_var = false;
bool stepperMotor_moveBackward_var = false;
bool stepperMotor_stop_var = false;

byte eggsTurnerState = 0;
bool turnEggs_cmd = false;

trigger stepperAutomaticControl_trigger;
trigger automaticControl_trigger;

unsigned int numberOfEggTurns_counter = 0;
/* END MOTORS SECTION */



/* RTC SECTION */
/*
   VCC   -->   5V
   GND   -->   GND
   SDA   -->   A4 (SDA)
   SCL   -->   A5 (SCL)
*/
#define RTC_IS_CONNECTED false

RTC_DS3231 rtc;

const unsigned long DEBUG_TRIGGER_INTERVAL = 10*1000; // 10seconds in milliseconds - DIVENTERA' VALORE DA HTML
bool turnEggs_cmd_fromRTC = false; // variabile che si ricorda appena è passato il tempo richiesto. Messa a false dalla action che aziona rotazione delle uova.

DateTime now;
DateTime lastTriggerTime; // Store the last trigger time

unsigned long now_millis, lastTriggerTime_millis;

#define MINUTES_CONFIGURATION false
int minutes_trigger_interval = 1; //  TESTING: 1min valore impostato da interfaccia per rotazione uova. Default 60*1.5h = 90min
int minutesToGO; // minuti mancanti alla prossima girata
int minutesGone; // minuti passati dalla precedente girata

#define SECONDS_CONFIGURATION true
int seconds_trigger_interval = 3600; //  TESTING: giriamo ogni 3 minuti
int secondsToGO; // minuti mancanti alla prossima girata
int secondsGone; // minuti passati dalla precedente girata

bool newDay = false; // per ricordarmi del passaggio del nuovo giorno
DateTime previousDay; // Store the last trigger time

/* END RTC SECTION */

float temp_sensor1, temp_sensor2, temp_sensor3;

//RECEIVING FROM ESP8266
#define MAX_NUMBER_OF_COMMANDS_FROM_BOARD 20
bool receivingDataFromBoard = false;
String receivedCommands[MAX_NUMBER_OF_COMMANDS_FROM_BOARD];
byte numberOfCommandsFromBoard;

// SENDING TO ESP8266
#define MAX_NUMBER_OF_COMMANDS_TO_BOARD 20
String listofDataToSend[MAX_NUMBER_OF_COMMANDS_TO_BOARD];
byte listofDataToSend_numberOfData = 0;

char bufferCharArray[35]; // buffer lo metto qui
// handling float numbers
char bufferChar[35];
char fbuffChar[15];

/* GENERAL */
bool gotTemperatures = false;

/* variabile che viene messa a true quando viene richiesto al motore di andare.
  La usi ogni qualvolta devi interrompere qualcosa per dare spazio al motore.
*/
bool inhibit_stepperMotorRunning = false; 

bool ledCheck = false; // variabile che fa il check del led PIN 13. rimane falsa, quindi tiene accesa il led. Appena faccio un accesso da HTML, allora resetto il led.

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(STEPPPER_MOTOR_STEP_PIN, OUTPUT);
  digitalWrite(STEPPPER_MOTOR_STEP_PIN, LOW);

  pinMode(STEPPPER_MOTOR_DIRECTION_PIN, OUTPUT);
  digitalWrite(STEPPPER_MOTOR_DIRECTION_PIN, LOW);  

  pinMode(STEPPPER_MOTOR_MS1_PIN, OUTPUT);
  digitalWrite(STEPPPER_MOTOR_MS1_PIN, LOW);

  pinMode(STEPPPER_MOTOR_MS2_PIN, OUTPUT);
  digitalWrite(STEPPPER_MOTOR_MS2_PIN, LOW);

  pinMode(STEPPPER_MOTOR_MS3_PIN, OUTPUT);
  digitalWrite(STEPPPER_MOTOR_MS3_PIN, LOW);

  pinMode(COOLING_EMERGENCY_FAN_PIN, OUTPUT);
  pinMode(CYCLE_TOGGLE_ANALOG0_PIN, OUTPUT);


  pinMode(MAIN_HEATER_PIN, OUTPUT);
  pinMode(AUX_HEATER_PIN, OUTPUT);

  pinMode(UPPER_FAN_PIN, OUTPUT);
  pinMode(LOWER_FAN_PIN, OUTPUT);

  // resetting an putting to low level FAN commands:
  delay(250);
  digitalWrite(UPPER_FAN_PIN, LOW); // logica negata, in connessione hw: normalmente chiuso per non dover eccitare costanemente il relè
  delay(250);
  digitalWrite(LOWER_FAN_PIN, LOW); // logica negata, in connessione hw: normalmente chiuso per non dover eccitare costanemente il relè

  pinMode(LEFT_INDUCTOR_PIN, INPUT);
  pinMode(RIGHT_INDUCTOR_PIN, INPUT);

  Serial.begin(SERIAL_SPEED);

  if(WATCHDOG_ENABLE){
    wdt_disable();
    wdt_enable(WDTO_2S);
  }

  /* TEMPERATURES SECTION */
  higherHysteresisLimit = 37.8;
  lowerHysteresisLimit = 37.4;

  sensors.begin();
  numberOfDevices = sensors.getDeviceCount();
  sensors.setWaitForConversion(false);
  sensors.requestTemperatures();
  lastTempRequest = millis(); 
  conversionTime_DS18B20_sensors = 750 / (1 << (12 - TEMPERATURE_PRECISION));  // res in {9,10,11,12}
  delay(4*conversionTime_DS18B20_sensors);


  if (numberOfDevices > MAX_SENSORS){
    Limit = MAX_SENSORS;
  }
  else{
    Limit = numberOfDevices;
  }
  
  for(byte index = 0; index < Limit; index++){
    if(sensors.getAddress(Thermometer[index], index)){
      sensors.setResolution(Thermometer[index], TEMPERATURE_PRECISION);
      //delay(750/ (1 << (12-TEMPERATURE_PRECISION)));
    }
  }

  temperature_heater_selection_upper_treshold = 37.0;
  temperature_heater_selection_lower_treshold = 36.8;
  
  /* END TEMPERATURES SECTION */

  dht.begin();

  if(RTC_IS_CONNECTED){
    /* RTC SECTION */
    if (!rtc.begin()) {
      //Serial.println("Couldn't find RTC");
      while (1);
    }

    if (rtc.lostPower()) {
      //Serial.println("RTC lost power, let's set the time!");
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    // Initialize last trigger time to current time
    lastTriggerTime = rtc.now();
    previousDay = rtc.now();
    /* END RTC SECTION */
  }
  else{
    lastTriggerTime_millis = millis();
  }

  delay(2500);
  serialFlush();

  digitalWrite(LED_BUILTIN, HIGH); // all'avvio accendo il LED_BUILTIN. Durante il funzionamento lo resetto. Se ritorno e lo vedo acceso, significa che ha agito il watchdog.
}

void loop() {    
  /* TEMPERATURES SECTION */
  if(!inhibit_stepperMotorRunning){
    if(millis() - lastTempRequest >= (4*conversionTime_DS18B20_sensors)){
      controlTemperatureIndex = 0;
      for(byte index = 0; index < Limit; index++){
        // Call the function to convert the device address to a char array
        addressToCharArray(Thermometer[index], addressCharArray);
        if(strcmp(addressCharArray, comparisonAddress) == 0){
          // calcolo dell'umidità
          humiditySensor_temperature = sensors.getTempC(Thermometer[index]);
          if(humiditySensor_temperature < 0.0){
            humiditySensor_temperature = 1.5;
          }
        }
        else{
          // gli altri li possiamo streammare verso html
          temperatures[controlTemperatureIndex] = sensors.getTempC(Thermometer[index]); // memorizza tutte le temperature che ci pensa l'oggetto temperatureController a gestirle
          if(temperatures[controlTemperatureIndex] < 0.0){
            temperatures[controlTemperatureIndex] = 1.5;
          }
          controlTemperatureIndex += 1;
        }     
        delay(5);
      }
      gotTemperatures = true;
    
      sensors.requestTemperatures();
      delay(10);
      lastTempRequest = millis();
    } 

    temperatureController.setTemperatureHysteresis(lowerHysteresisLimit, higherHysteresisLimit);
    temperatureController.setControlModality(temperatureControlModality); 
    
    if(gotTemperatures){
      // ha senso fare l'update solo quando arrivano le nuove temperature da valutare
      temperatureController.periodicRun(temperatures, 3); // 3 sono i sensori che usiamo per fare il controllo della temperatura

      /*
        Nuova logica di controllo:
          se la temperatura è sotto ad un certo livello dobbiamo scaldare molto e uso il riscaldatore principale, che assorbe 2A e scalda di più
          Se invece è sotto un certo livello, allora scaldo con il riscaldatore ausiliario per essere più precisi nel riscaldamento.
          Devo fare un po' di isteresi, che scrivo applicativa, altrimenti rischio di ballare fra un riscaldatore e l'altro

          mainHeaterSelected true -> 
      */
      // Hysteresis control
      if(!SINGLE_SMALL_HEATER_PRESENT){
        /* Selezione del riscaldatore in base alla temperatura */
        if(temperatureController.getActualTemperature() > temperature_heater_selection_upper_treshold && mainHeaterSelected){ // Appena passiamo la temperatura limite superiore allora attivo il secondo riscaldatore
          mainHeaterSelected = false;
        } else if(temperatureController.getActualTemperature() < temperature_heater_selection_lower_treshold && !mainHeaterSelected){ // Se scendo troppo allora seleziono il riscaldatore più potente
          mainHeaterSelected = true;
        }

        /* generazione dei trigger */
        mainHeaterSeleted_trigger.periodicRun(mainHeaterSelected);

        /*
          Questo codice mi serve per spegnere con un po' di delay un riscaldatore quando passiamo all'altro. Ricorda che non voglio avere switch contemporanei dei relè,
          per ridurre il problema dell'assorbimento di corrente.
          Quindi, se devo switchare riscaldatore mentre è acceso l'altro, mi prendo un po' di delay.
        */
        if(mainHeaterSeleted_trigger.catchRisingEdge()){ // switchare da AUX --> MAIN
          if(auxHeater_var){ // se sto scaldando con l'aux allora lo spengo + delay
            auxHeater_var = false;
            digitalWrite(AUX_HEATER_PIN, auxHeater_var);
            delay(250);
          }
        }

        if(mainHeaterSeleted_trigger.catchFallingEdge()){ // switchare da MAIN --> AUX
          if(mainHeater_var){ // se sto scaldando con il main allora lo spengo + delay
            mainHeater_var = false;
            digitalWrite(MAIN_HEATER_PIN, mainHeater_var);
            delay(250);
          }
        }

        /* scaldiamo in base al riscaldatore selezionato */
        if(temperatureController.getOutputState()){ 
          if(mainHeaterSelected){
            mainHeater_var = true;
            digitalWrite(MAIN_HEATER_PIN, mainHeater_var);
          }
          else{
            auxHeater_var = true;
            digitalWrite(AUX_HEATER_PIN, auxHeater_var);
          }
        }
        else{
          if(mainHeaterSelected){
            mainHeater_var = false;
            digitalWrite(MAIN_HEATER_PIN, mainHeater_var);
          }
          else{
            auxHeater_var = false;
            digitalWrite(AUX_HEATER_PIN, auxHeater_var);
          }
        }

        temperatureController_outputState_trigger.periodicRun(temperatureController.getOutputState());

        if(temperatureController_outputState_trigger.catchRisingEdge() || temperatureController_outputState_trigger.catchFallingEdge()){
          delay(250);
        }
      }
      else{
        /* SINGLE_SMALL_HEATER_PRESENT true significa che c'è solo un riscaldatore piccolo da 100W. Uso sempre quello. */
        if(temperatureController.getOutputState()){ 
          auxHeater_var = true;
          digitalWrite(AUX_HEATER_PIN, auxHeater_var);
        }
        else{
          auxHeater_var = false;
          digitalWrite(AUX_HEATER_PIN, auxHeater_var);
        }
      }

      //SINGLE_SMALL_HEATER_PRESENT tue: seconda versione, ci metto la ventolina di emergenza per raffreddamento.
      if(SINGLE_SMALL_HEATER_PRESENT){
        /* isteresi per vedere se siamo oltre il livello alto della temperatura */
        if(temperatureController.getActualTemperature() > 38.2 && tooHighTemperature){ // Appena passiamo la temperatura limite superiore allora attivo la ventolina di raffreddamento
          digitalWrite(COOLING_EMERGENCY_FAN_PIN, HIGH);
        } else if(temperatureController.getActualTemperature() < 38.0 && !tooHighTemperature){ // Appena ristabilizzo sotto i 38.0°, allora spengo la ventolina
          digitalWrite(COOLING_EMERGENCY_FAN_PIN, LOW);
        }
      }
    }
  }
  else{
    // mentre inibisco il controllo di temperatura perché il motore gira, è opportuno: a regime, con temperatura di riferimento raggiunta, anche solo 30s di rotazione full riscaldamento pososno creare problema di surriscaldamento.
    digitalWrite(MAIN_HEATER_PIN, false);
    //delay(150);    // questo codice gira con la ciclicità del motore, quidni non posso mettere il delay. No problem, tanto gli heater sono accesi/spenti in modo che ce ne sia uno per volta on. Quindi posso chiamare in contemporanea lo spegnimento dei due heater.
    digitalWrite(AUX_HEATER_PIN, false);
  }
  /* END TEMPERATURES SECTION */




  /* HUMIDITY COMPUTATION SECTION */
  /* DHT22 sensor */    
  if(!inhibit_stepperMotorRunning){
    humidity_fromDHT22 = dht.readHumidity();
    temp_fromDHT22 = dht.readTemperature();  
    // DS18B20 misura temperatura bulbo umido 
    wetTermometer_fromDS18B20 = humiditySensor_temperature; // temperatura misurata dal bulbo umido
    temperatureMeanValue = temperatureController.getMeanTemperature(); // temperatura ambiente incubatrice
  }  
  /* END HUMIDITY COMPUTATION SECTION */




  /* INDUCTOR INPUT SECTION */
  leftInductor_input.periodicRun();
  rightInductor_input.periodicRun();
  /* END INDUCTOR INPUT SECTION */



  /* STEPPER MOTOR CONTROL SECTION */
  eggsTurnerStepperMotor.periodicRun();

  /* CHIAMATA STOP DI EMERGENZA, se dovessi leggere un induttore limitatore. */
  /*
  leftInductor_TON.periodicRun(leftInductor_input.getCurrentInputState());
  rightInductor_TON.periodicRun(rightInductor_input.getCurrentInputState());

  if(leftInductor_TON.getTON_OutputEdgeType() || rightInductor_TON.getTON_OutputEdgeType()){
    eggsTurnerStepperMotor.stopMotor();
  }
  */
  
 
  if(stepperAutomaticControl_var){
    if(RTC_IS_CONNECTED){
      /* RTC SECTION */
      now = rtc.now();

      if(eggsTurnerState >= 2){
        turnEggs_cmd_fromRTC = false;

        if(eggsTurnerState == 2 || eggsTurnerState == 4){
          if(MINUTES_CONFIGURATION){
            // Check if the trigger interval has passed: MINUTI
            minutesGone = computeTimeDifference_inMinutes(now, lastTriggerTime);
            minutesToGO = minutes_trigger_interval - minutesGone;

            if(minutesGone >= minutes_trigger_interval) {
              turnEggs_cmd_fromRTC = true;
            }
          }

          if(SECONDS_CONFIGURATION){
            // Check if the trigger interval has passed: MINUTI
            secondsGone = computeTimeDifference_inSeconds(now, lastTriggerTime);
            secondsToGO = seconds_trigger_interval - secondsGone;

            if(secondsGone >= seconds_trigger_interval) {
              turnEggs_cmd_fromRTC = true;
            }
          }
        }
        else{
          if(MINUTES_CONFIGURATION){
            // Check if the trigger interval has passed: MINUTI
            minutesGone = minutes_trigger_interval;
            minutesToGO = 0;
          }

          if(SECONDS_CONFIGURATION){
            // Check if the trigger interval has passed: MINUTI
            secondsGone = seconds_trigger_interval;
            secondsToGO = 0;
          }
        }
      }

      if (now.day() != previousDay.day()) {
        // giorno passato, azzero il contatore di girate delle uova
        numberOfEggTurns_counter = 0;
        newDay = true;
        previousDay = now;
      }
      else{
        newDay = false;
      }
      
      // Check for overflow ??
      if (now.unixtime() < 0) {
        //Serial.println("RTC overflow detected. Resetting...");
        resetRTC();
        return; // Exit loop to reset
      }

      turnEggs_cmd = turnEggs_cmd_fromRTC; // lascio la possibilità di avere degli OR di condizioni
      /* END RTC SECTION */
    }
    else{
      now_millis = millis();

      if(eggsTurnerState >= 2){
        turnEggs_cmd = false;

        if(eggsTurnerState == 2 || eggsTurnerState == 4){
          // Check if the trigger interval has passed: MINUTI
          secondsGone = floor( (now_millis - lastTriggerTime_millis) / 1000.0);
          secondsToGO = seconds_trigger_interval - secondsGone;

          if(secondsGone >= seconds_trigger_interval) {
            turnEggs_cmd = true;
          }
        }
        else{
          // Check if the trigger interval has passed: MINUTI
          secondsGone = seconds_trigger_interval;
          secondsToGO = 0;
        }
      }
    }    

      

    // direzione oraria = forward = verso l'induttore di destra (vedendo da dietro l'incubatrice)
    switch(eggsTurnerState){
      case 0: // ZEROING
        // lascio stato aperto per eventuale abilitazione della procedura di azzeramento da parte dell'operatore.
        if(leftInductor_input.getInputState()){ // se leggo già induttore, inutile comandare un bw. Sono già azzerato.
          // home position is reached - full left
          eggsTurnerStepperMotor.stopMotor();
          if(RTC_IS_CONNECTED){
            lastTriggerTime = now; // Update last trigger time
          }
          else{
            lastTriggerTime_millis = now_millis;
          }          
          eggsTurnerState = 2;
        }
        else{
          eggsTurnerStepperMotor.moveBackward(STEPPER_MOTOR_SPEED_DEFAULT);
          eggsTurnerState = 1;
        }        
        break;
      case 1: // WAIT_TO_REACH_LEFT_SIDE_INDUCTOR
        if(leftInductor_input.getInputState()){
          // home position is reached - full left
          eggsTurnerStepperMotor.stopMotor();
          if(RTC_IS_CONNECTED){
            lastTriggerTime = now; // Update last trigger time
          }
          else{
            lastTriggerTime_millis = now_millis;
          } 
          eggsTurnerState = 2;
        }
        break;
      case 2: // WAIT_FOR_TURN_EGGS_COMMAND_STATE --> will rotate from left to right (CW direction)
          if(turnEggs_cmd){
            eggsTurnerStepperMotor.moveForward(STEPPER_MOTOR_SPEED_DEFAULT);
            numberOfEggTurns_counter += 1;
            eggsTurnerState = 3;
          }
        break;
      case 3: // WAIT_TO_REACH_RIGHT_SIDE_INDUCTOR
          if(rightInductor_input.getInputState()){
            eggsTurnerStepperMotor.stopMotor();
            if(RTC_IS_CONNECTED){
              lastTriggerTime = now; // Update last trigger time
            }
            else{
              lastTriggerTime_millis = now_millis;
            } 
            eggsTurnerState = 4;
          }
        break;
      case 4: // WAIT_FOR_TURN_EGGS_COMMAND_STATE --> will rotate from right to left (CCW direction)
          if(turnEggs_cmd){
            eggsTurnerStepperMotor.moveBackward(STEPPER_MOTOR_SPEED_DEFAULT);
            numberOfEggTurns_counter += 1;
            eggsTurnerState = 5;
          }
        break;
      case 5: // WAIT_TO_REACH_LEFT_SIDE_INDUCTOR
          if(leftInductor_input.getInputState()){
            eggsTurnerStepperMotor.stopMotor();
            if(RTC_IS_CONNECTED){
              lastTriggerTime = now; // Update last trigger time
            }
            else{
              lastTriggerTime_millis = now_millis;
            } 
            eggsTurnerState = 2;
          }
        break;
      default:
        break;
    }

    /*
    Serial.print(secondsGone);
    Serial.print("  ");
    Serial.print(turnEggs_cmd);
    Serial.print("  ");
    Serial.print(eggsTurnerState);
    Serial.println();
    */
  }
  else{
    if(stepperAutomaticControl_trigger.catchFallingEdge()){ // catch della rimozione del controllo automatico: chiamo lo stop del motore.
      eggsTurnerStepperMotor.stopMotor();
      eggsTurnerState = 0; 
    }

    if(stepperMotor_moveForward_var){
      eggsTurnerStepperMotor.moveForward(STEPPER_MOTOR_SPEED_DEFAULT);
    }
    else if(stepperMotor_moveBackward_var){
      eggsTurnerStepperMotor.moveBackward(STEPPER_MOTOR_SPEED_DEFAULT);
    }
    else if(stepperMotor_stop_var){
      eggsTurnerStepperMotor.stopMotor();
    }

    //clear variables
    stepperMotor_moveForward_var = false;
    stepperMotor_moveBackward_var = false;
    stepperMotor_stop_var = false;
  }  
  /* END STEPPER MOTOR CONTROL SECTION */



  /* SERIAL COMMUNICATION FROM ARDUINO TO ESP8266 */
  if(!inhibit_stepperMotorRunning){
    if(gotTemperatures){
      gotTemperatures = false;
      // riempo i dati per la trasmissione
      listofDataToSend_numberOfData = 0; // ad ogni giro lo azzero    

      strcpy(bufferChar, "<t1, ");
      dtostrf( temperatures[0], 1, 1, fbuffChar); 
      listofDataToSend[listofDataToSend_numberOfData] = strcat(strcat(strcat(bufferChar, fbuffChar), ">"), "\0");
      listofDataToSend_numberOfData++;

      strcpy(bufferChar, "<t2, ");
      dtostrf( temperatures[1], 1, 1, fbuffChar); 
      listofDataToSend[listofDataToSend_numberOfData] = strcat(strcat(strcat(bufferChar, fbuffChar), ">"), "\0");
      listofDataToSend_numberOfData++; 

      strcpy(bufferChar, "<t3, ");
      dtostrf( temperatures[2], 1, 1, fbuffChar); 
      listofDataToSend[listofDataToSend_numberOfData] = strcat(strcat(strcat(bufferChar, fbuffChar), ">"), "\0");
      listofDataToSend_numberOfData++;

      strcpy(bufferChar, "<aT, "); // actualTemperature
      dtostrf(temperatureController.getActualTemperature(), 1, 1, fbuffChar); 
      listofDataToSend[listofDataToSend_numberOfData] = strcat(strcat(strcat(bufferChar, fbuffChar), ">"), "\0");
      listofDataToSend_numberOfData++;
    
      strcpy(bufferChar, "<hHL, "); //higher Hysteresis Limit from Arduino
      dtostrf(higherHysteresisLimit, 1, 1, fbuffChar); 
      listofDataToSend[listofDataToSend_numberOfData] = strcat(strcat(strcat(bufferChar, fbuffChar), ">"), "\0");
      listofDataToSend_numberOfData++;

      strcpy(bufferChar, "<lHL, "); //lower Hysteresis Limit from Arduino
      dtostrf(lowerHysteresisLimit, 1, 1, fbuffChar); 
      listofDataToSend[listofDataToSend_numberOfData] = strcat(strcat(strcat(bufferChar, fbuffChar), ">"), "\0");
      listofDataToSend_numberOfData++;

      // feedback about mainHeater state
      listofDataToSend[listofDataToSend_numberOfData] = mainHeater_var ? "<mHO, 1>":"<mHO, 0>"; // converting bool to string
      listofDataToSend_numberOfData++;

      // feedback about auxHeater state
      listofDataToSend[listofDataToSend_numberOfData] = auxHeater_var ? "<aHO, 1>":"<aHO, 0>"; // converting bool to string
      listofDataToSend_numberOfData++;
      
      // feedback about TEMPERATURE CONTROL MODALITY value
      sprintf(bufferCharArray, "<TMP07, %d>", temperatureControlModality); //sprintf function returns the number of characters written to the array
      listofDataToSend[listofDataToSend_numberOfData] = bufferCharArray;
      listofDataToSend_numberOfData++;

      // humidity misurata dal DHT22
      strcpy(bufferChar, "<hDHT, ");
      dtostrf(humidity_fromDHT22, 1, 1, fbuffChar); 
      listofDataToSend[listofDataToSend_numberOfData] = strcat(strcat(strcat(bufferChar, fbuffChar), ">"), "\0");
      listofDataToSend_numberOfData++;

      // temperatura del bulbo bagnato misurata da DS18B20 temperatureWet_fromDS18B20
      strcpy(bufferChar, "<tWDS, ");
      dtostrf(wetTermometer_fromDS18B20, 1, 1, fbuffChar); 
      listofDataToSend[listofDataToSend_numberOfData] = strcat(strcat(strcat(bufferChar, fbuffChar), ">"), "\0");
      listofDataToSend_numberOfData++;

      // valore medio della temperatura nella incubatrice  temperatureMeanValue
      strcpy(bufferChar, "<tMV, ");
      dtostrf(temperatureMeanValue, 1, 1, fbuffChar); 
      listofDataToSend[listofDataToSend_numberOfData] = strcat(strcat(strcat(bufferChar, fbuffChar), ">"), "\0");
      listofDataToSend_numberOfData++;

      //  numero di girate di uova numberOfEggTurns_counter = nET	
      sprintf(bufferCharArray, "<nET, %d>", numberOfEggTurns_counter); //sprintf function returns the number of characters written to the array
      listofDataToSend[listofDataToSend_numberOfData] = bufferCharArray;
      listofDataToSend_numberOfData++;

      if(ENABLE_SERIAL_PRINT_TO_ESP8266){
        if(listofDataToSend_numberOfData > 0){
          Serial.print('#'); // SYMBOL TO START BOARDS TRANSMISSION
          for(byte i = 0; i < listofDataToSend_numberOfData; i++){
            Serial.print(listofDataToSend[i]); 
          }
          Serial.print('@'); // SYMBOL TO END BOARDS TRANSMISSION
        }
      }
    }
  }
  

  // appena il buffer è pieno, mi blocco a leggerlo. Significa che ESP8266 ha pubblicato dei dati.
  if(Serial.available() > 0){ 
      numberOfCommandsFromBoard = readFromBoard(); // from ESP8266. It has @ as terminator character
      if(numberOfCommandsFromBoard > 0 && !ledCheck){
        // La prima volta in cui ricevo un comando spegno il leg. Significa che mi sono collegato con hmiHTML, quindi ho avuto il tempo di fare il ledCheck
        digitalWrite(LED_BUILTIN, LOW);
        ledCheck = true;
      }
      // Guardiamo che comandi ci sono arrivati
      for(byte j = 0; j < numberOfCommandsFromBoard; j++){
        String tempReceivedCommand = receivedCommands[j];
        //Serial.println(tempReceivedCommand);
        if(tempReceivedCommand.indexOf("STP01") >= 0){ //stepperMotorForwardOn
          stepperMotor_moveForward_var = true;
        }
        if(tempReceivedCommand.indexOf("STP02") >= 0){ //stepperMotorForwardOff
          stepperMotor_stop_var = true;
        }
        if(tempReceivedCommand.indexOf("STP03") >= 0){ //stepperMotorBackwardOn
          stepperMotor_moveBackward_var = true;
        }
        if(tempReceivedCommand.indexOf("STP04") >= 0){ //stepperMotorBackwardOff
          stepperMotor_stop_var = true;
        }
        /* ELIMINAZIONE DEL CONTROLLO AUTOMATICO: DEFAULT A TRUE
        if(tempReceivedCommand.indexOf("STP05") >= 0){ //stepperMotorAutomaticControlOn
          stepperAutomaticControl_var = true;
        }
        if(tempReceivedCommand.indexOf("STP06") >= 0){ //stepperMotorAutomaticControlOff
          stepperAutomaticControl_var = false;
        }
        */
        if(tempReceivedCommand.indexOf("TMP01") >= 0){ //mainHeaterOn
          mainHeater_var = true;
        }
        if(tempReceivedCommand.indexOf("TMP02") >= 0){ //mainHeaterOff
          mainHeater_var = false;
        }
        if(tempReceivedCommand.indexOf("TMP03") >= 0){ //auxHeaterOn
          auxHeater_var = true;
        }
        if(tempReceivedCommand.indexOf("TMP04") >= 0){ //auxHeaterOff
          auxHeater_var = false;
        }
        if(tempReceivedCommand.indexOf("ACT01") >= 0){ //upperFanOn
          upperFan_var = true;
        }
        if(tempReceivedCommand.indexOf("ACT02") >= 0){ //upperFanOff
          upperFan_var = false;
        }
        if(tempReceivedCommand.indexOf("ACT03") >= 0){ //lowerFanOn
          lowerFan_var = true;
        }
        if(tempReceivedCommand.indexOf("ACT04") >= 0){ //lowerFanOff
          lowerFan_var = false;
        }
        /* ELIMINAZIONE DEL CONTROLLO AUTOMATICO: DEFAULT A TRUE
        if(tempReceivedCommand.indexOf("GNR01") >= 0){ //automaticControlOn
          automaticControl_var = true;
        }
        if(tempReceivedCommand.indexOf("GNR02") >= 0){ //automaticControlOff
          automaticControl_var = false;
        }
        */
        if(tempReceivedCommand.indexOf("TMP05") >= 0){ //setting higherHysteresisLimit from ESP8266 HMTL page
          higherHysteresisLimit = getFloatFromString(tempReceivedCommand, ',');
        }
        if(tempReceivedCommand.indexOf("TMP06") >= 0){ //setting lowerHysteresisLimit from ESP8266 HMTL page
          lowerHysteresisLimit = getFloatFromString(tempReceivedCommand, ',');
        }
        if(tempReceivedCommand.indexOf("TMP07") >= 0){ //setting TEMPERATURE CONTROL MODALITY from ESP8266 HMTL page
          // 1: actualTemperature = maxValue
          // 2: actualTemperature = meanValue
          temperatureControlModality = getIntFromString(tempReceivedCommand, ',');
        }
      }
  }

  /* analisi sui comandi ricevuti */
  stepperAutomaticControl_trigger.periodicRun(stepperAutomaticControl_var);
  automaticControl_trigger.periodicRun(automaticControl_var);
  

  inhibit_stepperMotorRunning = eggsTurnerStepperMotor.get_stepCommand(); 
  
  if(WATCHDOG_ENABLE){
    wdt_reset();
  }  
}

int readFromBoard(){ // returns the number of commands received
  receivingDataFromBoard = true;
  byte rcIndex = 0;
  char bufferChar[30];
  bool saving = false;
  bool enableReading = false;
  byte receivedCommandsIndex = 0;

  unsigned long  startReceiving; // mi ricordo appena entro in while loop

  while(receivingDataFromBoard){
    // qui è bloccante...assumo che prima o poi arduino pubblichi
    if(Serial.available() > 0){ // no while, perché potrei avere un attimo il buffer vuoto...senza aver ancora ricevuto il terminatore
      startReceiving = millis(); // ogni volta in cui leggo resetto il timer
      char rc = Serial.read(); 

      if(rc == '#'){ // // SYMBOL TO START TRANSMISSION (tutto quello che c'era prima era roba spuria che ho pulito)
        enableReading = true;
      }

      if(enableReading){
        if(rc == '<'){ // SYMBOL TO START MESSAGE
          saving = true;
        }
        else if(rc == '>'){ // SYMBOL TO END MESSAGE
          bufferChar[rcIndex] = '\0';
          receivedCommands[receivedCommandsIndex] = bufferChar;
          receivedCommandsIndex ++;
          rcIndex = 0;
          saving = false;// starting char
        }
        else if(rc == '@'){ // SYMBOL TO END BOARDS TRANSMISSION
          receivingDataFromBoard = false; // buffer vuoto, vado avanti
          //enableReading = false
        }
        else{
          if(saving){
            bufferChar[rcIndex] = rc;
            rcIndex ++;
          }
        }
      }
    }
    else{
      // timer che conta perché non riceviamo più e mi fa uscire??
      // se sono qui è perché sto aspettando, ma non ricevendo
      if((millis() - startReceiving) > 750){ // se passo in attesa più di 750ms, allora intervengo e mando fuori
        receivingDataFromBoard = false;
      }
    }
  }
  return receivedCommandsIndex;
}

float getFloatFromString(String string, char divider){
  int index;
  for(byte i =0; i < string.length(); i++) {
    char c = string[i];
    
    if(c == divider){
      index = i + 2;
      break;
    }
  }

  return string.substring(index, string.length()).toFloat();
}

int getIntFromString(String string, char divider){
  int index;
  for(byte i =0; i < string.length(); i++) {
    char c = string[i];
    
    if(c == divider){
      index = i + 2;
      break;
    }
  }

  return string.substring(index, string.length()).toInt();
}

// Function to convert a byte to its hexadecimal representation
void byteToHex(uint8_t byteValue, char *hexValue) {
  uint8_t highNibble = byteValue >> 4;
  uint8_t lowNibble = byteValue & 0x0F;
  hexValue[0] = highNibble < 10 ? '0' + highNibble : 'A' + (highNibble - 10);
  hexValue[1] = lowNibble < 10 ? '0' + lowNibble : 'A' + (lowNibble - 10);
}

// Function to print a device address
void addressToCharArray(DeviceAddress deviceAddress, char *charArray) {
  for (uint8_t i = 0; i < 8; i++) {
    byteToHex(deviceAddress[i], &charArray[i * 2]);
  }
  // Add null terminator at the end of the char array
  charArray[16] = '\0';
}

int computeTimeDifference_inMinutes(DateTime currentTime, DateTime lastTrigger){
  // unixtime --> is a standard way of representing time as a single numeric value
  unsigned long diffSeconds = currentTime.unixtime() - lastTrigger.unixtime();
  int differenceInMinutes = (diffSeconds % 3600) / 60;

  return differenceInMinutes;
}

int computeTimeDifference_inSeconds(DateTime currentTime, DateTime lastTrigger){
  // unixtime --> is a standard way of representing time as a single numeric value
  unsigned long diffSeconds = currentTime.unixtime() - lastTrigger.unixtime();

  return diffSeconds;
}

// Function to reset the RTC module
void resetRTC() {
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void serialFlush(){
  while(Serial.available() > 0) {
    char t = Serial.read();
  }
}
