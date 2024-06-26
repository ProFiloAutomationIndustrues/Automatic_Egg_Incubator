from flask import Flask, render_template
from flask_socketio import SocketIO, emit
import random
import time
import threading
import queue

app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app)

temperature_queue = queue.Queue()

@app.route('/')
def index():
    return render_template('index.html')

def monitoring_temperatures_task():
    while True:
        data = {
            'temp1': random.uniform(20, 25),
            'temp2': random.uniform(20, 25),
            'temp3': random.uniform(20, 25),
            'mainHeater': random.choice([True, False]),
            'auxHeater': random.choice([True, False]),
            'machineState': random.randint(0, 5)
        }
        # Send data to HTML page
        socketio.emit('data_update', data)
        
        # Send data to periodic_task via the queue
        temperature_queue.put(data)
        
        # Sleep for 100ms
        time.sleep(0.1)

def periodic_task():
    while True:
        try:
            # Perform other actions here
            #print("Periodic task is doing other things...")
            time.sleep(1)  # Simulate doing something else for 1 second
            
            # Check for new data in the queue
            if not temperature_queue.empty():
                data = temperature_queue.get()
                # Process the temperature data
                '''
                print(f"Processing temperature data: {data}")
                if data['temp1'] > 24:
                    print("Alert: Temperature 1 exceeds threshold!")
                if data['temp2'] > 24:
                    print("Alert: Temperature 2 exceeds threshold!")
                if data['temp3'] > 24:
                    print("Alert: Temperature 3 exceeds threshold!")
                '''
        except Exception as e:
            print(f"Error in periodic_task: {e}")

def send_async_messages():
    colors = ['red', 'orange', 'yellow', 'green', 'blue']
    messages = [
        "Critical: System failure detected!",
        "Warning: High temperature recorded.",
        "Note: System maintenance required.",
        "Info: All systems operational."
    ]
    priorities = {
        'red': 0,
        'orange': 1,
        'yellow': 2,
        'green': 3,
        'blue': 4
    }
    while True:
        message = random.choice(messages)
        color = random.choice(colors)
        socketio.emit('async_message', {'text': message, 'color': color})
        time.sleep(random.randint(5, 15))
        
def send_async_messages_FILO():
    while True:
        message = "Messaggio da funzione Aync Di Filo"
        color = 'red'
        socketio.emit('async_message', {'text': message, 'color': color})
        time.sleep(10)


@socketio.on('command')
def handle_command(data):
    print(f"Received command: {data['cmd']} from button {data['button']}")
    if data['cmd'] == 'start':
        # Handle start command
        print("Handling start command")
    elif data['cmd'] == 'stop':
        # Handle stop command
        print("Handling stop command")
    elif data['cmd'] == 'reset':
        # Handle reset command
        print("Handling reset command")
        socketio.emit('clear_messages')

@socketio.on('number')
def handle_number(data):
    print("DATA: ")
    print(data)
    print(f"Received number: {data['number']}")
    # Handle the number input, for example:
    process_number(data['number'])
    
@socketio.on('higherHysteresisLimit')
def handle_higher_hysteresis_limit(data):
    print("DATA: ")
    print(data)
    '''
    print(f"Received higher hysteresis limit: {data['higherHysteresisLimit']}")
    new_limit = data['higherHysteresisLimit']
    # Process the higher hysteresis limit
    process_higher_hysteresis_limit(new_limit)
    # Optionally, send a message back to the client
    socketio.emit('message', {'text': f"Higher Hysteresis Limit set to {new_limit}", 'color': 'blue'})
    '''

@socketio.on('lowerHysteresisLimit')
def handle_lower_hysteresis_limit(data):
    print(f"Received lower hysteresis limit: {data['lowerHysteresisLimit']}")
    new_limit = data['lowerHysteresisLimit']
    # Process the lower hysteresis limit
    process_lower_hysteresis_limit(new_limit)
    # Optionally, send a message back to the client
    socketio.emit('message', {'text': f"Lower Hysteresis Limit set to {new_limit}", 'color': 'blue'})

def process_number(number):
    # Implement your logic to process the number
    print(f"Processing number: {number}")

def process_higher_hysteresis_limit(limit):
    # Implement your logic to process the higher hysteresis limit
    print(f"Processing higher hysteresis limit: {limit}")

def process_lower_hysteresis_limit(limit):
    # Implement your logic to process the lower hysteresis limit
    print(f"Processing lower hysteresis limit: {limit}")

if __name__ == '__main__':
    threading.Thread(target=monitoring_temperatures_task).start()
    threading.Thread(target=periodic_task).start()
    threading.Thread(target=send_async_messages).start()
    threading.Thread(target=send_async_messages_FILO).start()
    socketio.run(app, host='0.0.0.0', port=5000)
