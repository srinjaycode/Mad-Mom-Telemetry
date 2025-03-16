# ------------- 3 Idiots ---------------

# all imports, if you are reproducing locally then you have to install all libraries with pip
import requests
import os
import time
from google import genai
from IPython.display import Audio

# API Keys 
GEMINI_API_KEY = "AIzaSyDU8Tumt4Exey92UeL6OmMoz7ZZVXqhAPQ" 
ELEVEN_LABS_API_KEY = "sk_9c83348aa1907eac3425150be0f454e592053f74accb13bc"

#settings
kind = "You are a kind mother talking to your favorite child, even if he is a goofball, ask him if he wants icecream, and stuff like that. You talk extremely fast, interrupt often, and demand immediate action."
angry = "You are an  mother. You are furious, impatient, and always yelling. Generate an extremely aggressive, fast-talking, nagging AI mother response. You talk slowly and caress."

name = "Mustafa"
thin = "twigs, flat like a paper and you hate it"
fat = "fatso, literal fatso monkey"
characteristics = "doesnt sleep on time, has a lot of body hair which smells."
hobby = "Plays too much football, horrible player. His stomach is shaped like a football"

# error checking
if not GEMINI_API_KEY:
    raise ValueError("Google Gemini API key is missing.")
if not ELEVEN_LABS_API_KEY:
    raise ValueError("Eleven Labs API key is missing.")

# Google Gemini AI Setup
HEADERS = {"x-api-key": GEMINI_API_KEY}
genai_client = genai.Client(api_key=GEMINI_API_KEY)

# initial sensor values
temp = "0 C"
speed = "0 km/h"
position = [0, 0]

# function for gemini prompting
def whatwouldmaasay():
    response = genai_client.models.generate_content(
        model="gemini-2.0-flash",
        contents=(
            f"You are speaking to a person, so speak normally and coherently,"
            f"{angry}"
            f"You have a ultrasonic, temperature and accelerometer sensors on your child, kid name is {name}"
            f"Your kid is {thin}"
            f"your kid also {characteristics} and {hobby}"
            f"Speak coherent english, dont use numbers or special characters, use special characters."
            f"Dont say numbers, and special characters"
            f"Distance: {position}, Speed: {speed}, Temperature: {temp}."
            f"Use the distance to say if kid is too close and going to crash, or too far, also use speed to say kid is going slow or fast, and use the temperature to say if kid is freezing or blazing hot,"
            f"Use this data to SCREAM and NAG in MAX 50 WORDS!"
        )
    )
    return response.text.strip()

# tts - convert the generated text to voice
def text_to_speech(text):  
    url = "https://api.elevenlabs.io/v1/text-to-speech/e32mynCa5wxYhGWUoxsr"  # Replace with actual voice ID
    headers = {
        "Content-Type": "application/json",
        "xi-api-key": ELEVEN_LABS_API_KEY,
    }
    data = {
        "text": text,
        "voice_settings": {
            "stability": 0.5,
            "similarity_boost": 0.7
        }
    }

    response = requests.post(url, json=data, headers=headers)
    if response.status_code == 200:
        audio_path = "mom_voice.mp3"
        with open(audio_path, "wb") as f:
            f.write(response.content)
        print("Audio saved as mom_voice.mp3")
        return audio_path
    else:
        print("Error:", response.text)
        return None

#function to run it on google colab
def play_audio_colab(audio_path):
    """Play audio in Google Colab using IPython.display.Audio."""
    if audio_path:
        return Audio(audio_path, autoplay=True)
    else:
        print("No valid audio file to play.")

# run it
nagging_message = whatwouldmaasay()
print("Generated Nagging:", nagging_message)
audio_file = text_to_speech(nagging_message)
play_audio_colab(audio_file)
