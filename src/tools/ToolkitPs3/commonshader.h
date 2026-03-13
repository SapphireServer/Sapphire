
#ifndef SAPPHIRE_COMMON_H
#define SAPPHIRE_COMMON_H

  GLuint compileShader( GLenum type, const char *source );
  GLuint createShaderProgram( const char *vertexSource, const char *fragmentSource );
#endif //SAPPHIRE_COMMON_H