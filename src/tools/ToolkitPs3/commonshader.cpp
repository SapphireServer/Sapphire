#include "Engine/GfxApi.h"
#include "Engine/ResourceManager.h"
#include "Engine/ShaderResource.h"

GLuint compileShader( GLenum type, const char *source )
{
  GLuint shader = glCreateShader( type );
  glShaderSource( shader, 1, &source, nullptr );
  glCompileShader( shader );

  GLint success;
  glGetShaderiv( shader, GL_COMPILE_STATUS, &success );
  if( !success )
  {
    char infoLog[ 512 ];
    glGetShaderInfoLog( shader, 512, nullptr, infoLog );
    printf( "Shader compilation failed: %s\n", infoLog );
    glDeleteShader( shader );
    return 0;
  }
  return shader;
}

GLuint createShaderProgram( const char *vertexSource, const char *fragmentSource )
{
  GLuint vertexShader = compileShader( GL_VERTEX_SHADER, vertexSource );
  GLuint fragmentShader = compileShader( GL_FRAGMENT_SHADER, fragmentSource );

  if( !vertexShader || !fragmentShader )
  {
    if( vertexShader )
      glDeleteShader( vertexShader );
    if( fragmentShader )
      glDeleteShader( fragmentShader );
    return 0;
  }

  GLuint program = glCreateProgram();
  glAttachShader( program, vertexShader );
  glAttachShader( program, fragmentShader );
  glLinkProgram( program );

  GLint success;
  glGetProgramiv( program, GL_LINK_STATUS, &success );
  if( !success )
  {
    char infoLog[ 512 ];
    glGetProgramInfoLog( program, 512, nullptr, infoLog );
    printf( "Shader linking failed: %s\n", infoLog );
    glDeleteProgram( program );
    program = 0;
  }

  glDeleteShader( vertexShader );
  glDeleteShader( fragmentShader );

  return program;
}