// An executable file that generates two different test vectors
// shouldpass.md contains a dictionnary of datatype/topic/value -> frame
// that should be identified successfully by any distribution
// shoudlfail.md contains a set of non valid frames

#include "telemetry.h"
#include "stdio.h"

FILE * output;

// Not used. Don't care
int32_t read(void * buf, uint32_t sizeToRead)
{
  return 0;
}

// Not used. Don't care
int32_t readable()
{
  return 0;
}

int32_t write(void * buf, uint32_t sizeToWrite)
{
  uint8_t * caster = (uint8_t*)(buf);
  for(uint32_t i = 0 ; i < sizeToWrite ; i++)
  {
      fprintf(output, "%02x", caster[i]);
  }
}

int32_t writeable()
{
  return 1;
}

void newentry(FILE * file, const char * topic, const char * msg)
{
  fputs("string", file);
  fputs("\t;\t", file);
  fputs(topic, file);
  fputs("\t;\t", file);
  fputs(msg, file);
  fputs("\t;\t", file);
  publish(topic,msg);
  fputs("\n", file);
}

void newentry_u8(FILE * file, const char * topic, uint8_t data)
{
  fputs("u8", file);
  fputs("\t;\t", file);
  fputs(topic, file);
  fputs("\t;\t", file);
  fprintf(file, "%hhu", data);
  fputs("\t;\t", file);
  publish_u8(topic,data);
  fputs("\n", file);
}

void newentry_u16(FILE * file, const char * topic, uint16_t data)
{
  fputs("u16", file);
  fputs("\t;\t", file);
  fputs(topic, file);
  fputs("\t;\t", file);
  fprintf(file, "%hu", data);
  fputs("\t;\t", file);
  publish_u16(topic,data);
  fputs("\n", file);
}

void newentry_u32(FILE * file, const char * topic, uint32_t data)
{
  fputs("u32", file);
  fputs("\t;\t", file);
  fputs(topic, file);
  fputs("\t;\t", file);
  fprintf(file, "%u", data);
  fputs("\t;\t", file);
  publish_u32(topic,data);
  fputs("\n", file);
}

void newentry_i8(FILE * file, const char * topic, int8_t data)
{
  fputs("i8", file);
  fputs("\t;\t", file);
  fputs(topic, file);
  fputs("\t;\t", file);
  fprintf(file, "%hhi", data);
  fputs("\t;\t", file);
  publish_i8(topic,data);
  fputs("\n", file);
}

void newentry_i16(FILE * file, const char * topic, int16_t data)
{
  fputs("i16", file);
  fputs("\t;\t", file);
  fputs(topic, file);
  fputs("\t;\t", file);
  fprintf(file, "%hi", data);
  fputs("\t;\t", file);
  publish_i16(topic,data);
  fputs("\n", file);
}

void newentry_i32(FILE * file, const char * topic, int32_t data)
{
  fputs("i32", file);
  fputs("\t;\t", file);
  fputs(topic, file);
  fputs("\t;\t", file);
  fprintf(file, "%i", data);
  fputs("\t;\t", file);
  publish_i32(topic,data);
  fputs("\n", file);
}

void newentry_f32(FILE * file, const char * topic, float data)
{
  fputs("f32", file);
  fputs("\t;\t", file);
  fputs(topic, file);
  fputs("\t;\t", file);
  fprintf(file, "%f", data);
  fputs("\t;\t", file);
  publish_f32(topic,data);
  fputs("\n", file);
}

int main()
{
  TM_transport transport;

  transport.write = write;
  transport.read = read;
  transport.readable = readable;
  transport.writeable = writeable;

  init_telemetry(&transport);

  output = NULL;
  output = fopen("valid_vectors.csv","w");
  if(output == NULL)
  {
    printf("Failure : Could not open file for write.");
    return -1;
  }

  // Test vectors
  newentry(output, "foo"             ,"bar");
  newentry(output, "foo with spaces" ,"bar with spaces");
  newentry(output, "0123456789"      ,"0123456789");
  newentry(output, "ABCD/EFGH:IJK"   ,"abcdefghijk");
  newentry(output, "lmnopqrstuv:123"   ,"wxyz");

  newentry_u8(output, "bar", 0);
  newentry_u8(output, "foo", 255);
  newentry_u8(output, "hello world", 127);

  newentry_u16(output, "abcdef", 0);
  newentry_u16(output, "bar", 65535);
  newentry_u16(output, "fooqux", 256);

  newentry_u32(output, "ghij", 0);
  newentry_u32(output, "test", 1);
  newentry_u32(output, "klmopq", 4294967295);
  newentry_u32(output, "rstuv", 65536);

  newentry_i8(output, "bar", 0);
  newentry_i8(output, "plus", 1);
  newentry_i8(output, "minus", -1);
  newentry_i8(output, "foo", -127);
  newentry_i8(output, "hello world", -127);

  newentry_i16(output, "abcdef", 0);
  newentry_i16(output, "minus", -1);
  newentry_i16(output, "plus", 1);
  newentry_i16(output, "bar", 32767);
  newentry_i16(output, "fooqux", -32767);

  newentry_i32(output, "ghij", 0);
  newentry_i32(output, "minus", -1);
  newentry_i32(output, "plus", 1);
  newentry_i32(output, "klmopq", 2147483647);
  newentry_i32(output, "rstuv", -2147483648);

  newentry_f32(output, "zeropos", 0.f);
  newentry_f32(output, "zeropos", -0.f);
  newentry_f32(output, "normally perfect", 61.f);
  newentry_f32(output, "other", 1.2e34);
  newentry_f32(output, "otherneg", -1.2e34);

  close(output);
  printf("Valid test vector generation success.\n");
  return 0;
}
