#include "speaker.hpp"

static int constexpr BAUDRATE_SERIAL = 9600;

Speaker::Speaker(unsigned char vol){
  serial_voice_module.begin(BAUDRATE_SERIAL);
  unsigned char volume[5] = {0xAA, 0x13, 0x01, vol, vol+0xBE};
  serial_voice_module.write(volume, 5);
};

void Speaker::play_file(unsigned char file_num){
  unsigned char play[6] = {0xAA, 0x07, 0x02, 0x00, file_num, file_num+0xB3};
  serial_voice_module.write(play, 6);
}