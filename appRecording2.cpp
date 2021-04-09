#include "RtAudio.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

int record( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
	    double streamTime, RtAudioStreamStatus status, void *userDara)
{
  if(status){
    std::cout << "Stream overflow detected!" << std::endl;
  }


  double* inputAudio = (double *)inputBuffer;
  std::cout << inputAudio[0] << std::endl;
  // input buffer is where the voice data is, do something with it!

  return 0;

}

int main()
{
  RtAudio adc;
  if( adc.getDeviceCount() < 1){
    std::cout << "\nNo audio devices found!\n";
    exit( 0 );
  }

  RtAudio::StreamParameters parameters;
  parameters.deviceId = adc.getDefaultInputDevice();
  parameters.nChannels = 2;
  parameters.firstChannel = 0;
  unsigned int sampleRate = 44100;
  unsigned int bufferFrames = 256; // 256 sample frames

  try{
    adc.openStream( NULL, &parameters, RTAUDIO_SINT16,
		    sampleRate, &bufferFrames, &record );
    adc.startStream();
  }
  catch ( RtAudioError& e){
    e.printMessage();
    exit( 0 );
  }

  char input;
  std::cout << "\n Recording ... press <enter> to quit.\n";
  std::cin.get( input );

  try {
    // Stop the stream
    adc.stopStream();
  }

  catch (RtAudioError& e){
    e.printMessage();
  }

  if ( adc.isStreamOpen() ){
    adc.closeStream();
  }

  return 0;
}
