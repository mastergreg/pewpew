#define ZeroMemory(p, sz) memset((p), 0, (sz))
//accumulator buffer
#include <math.h>             // We'll Need Some Math

float   angle;              // Used To Rotate The Helix
float   vertexes[4][3];           // Holds Float Info For 4 Sets Of Vertices
float   normal[3];            // An Array To Store The Normal Data
GLuint    BlurTexture;            // An Unsigned Int To Store The Texture Number

void ViewOrtho()              // Set Up An Ortho View
{
  glMatrixMode(GL_PROJECTION);          // Select Projection
  glPushMatrix();             // Push The Matrix
  glLoadIdentity();           // Reset The Matrix
  glOrtho( 0, 640 , 480 , 0, -1, 1 );       // Select Ortho Mode (640x480)
  glMatrixMode(GL_MODELVIEW);         // Select Modelview Matrix
  glPushMatrix();             // Push The Matrix
  glLoadIdentity();           // Reset The Matrix
}

void ViewPerspective()              // Set Up A Perspective View
{
  glMatrixMode( GL_PROJECTION );          // Select Projection
  glPopMatrix();              // Pop The Matrix
  glMatrixMode( GL_MODELVIEW );         // Select Modelview
  glPopMatrix();              // Pop The Matrix
}
GLuint EmptyTexture()             // Create An Empty Texture
{
  GLuint txtnumber;           // Texture ID
  unsigned int* data;           // Stored Data
  // Create Storage Space For Texture Data (128x128x4)
  data = (unsigned int*)new GLuint[((128 * 128)* 4 * sizeof(unsigned int))];
  //After allocating space we zero it using the ZeroMemory function, 
  //passing the pointer (data) and the size of memory to be "zeroed".
  //A semi important thing to note is that we set the magnification 
  //and minification methods to GL_LINEAR. That's because we will be 
  //stretching our texture and GL_NEAREST looks quite bad if stretched.  
  ZeroMemory(data,((128 * 128)* 4 * sizeof(unsigned int))); // Clear Storage Memory
  glGenTextures(1, &txtnumber);         // Create 1 Texture
  glBindTexture(GL_TEXTURE_2D, txtnumber);      // Bind The Texture
  glTexImage2D(GL_TEXTURE_2D, 0, 4, 128, 128, 0,
      GL_RGBA, GL_UNSIGNED_BYTE, data);     // Build Texture Using Information In data
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

  delete [] data;             // Release data

  return txtnumber;           // Return The Texture ID
}
void RenderToTexture()              // Renders To A Texture
{
  glViewport(0,0,128,128);          // Set Our Viewport (Match Texture Size)
  lv.display();             // Render The Helix
  glBindTexture(GL_TEXTURE_2D,BlurTexture);     // Bind To The Blur Texture
  // Copy Our ViewPort To The Blur Texture (From 0,0 To 128,128... No Border)
  glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 0, 0, 128, 128, 0);
  glClearColor(0.0f, 0.0f, 0.5f, 0.5);        // Set The Clear Color To Medium Blue
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // Clear The Screen And Depth Buffer
  glViewport(0 , 0,640 ,480);         // Set Viewport (0,0 to 640x480)
}
void DrawBlur(int times, float inc)         // Draw The Blurred Image
{
  float spost = 0.0f;           // Starting Texture Coordinate Offset
  float alphainc = 0.9f / times;          // Fade Speed For Alpha Blending
  float alpha = 0.2f;           // Starting Alpha Value

  // Disable AutoTexture Coordinates
  glDisable(GL_TEXTURE_GEN_S);
  glDisable(GL_TEXTURE_GEN_T);

  glEnable(GL_TEXTURE_2D);          // Enable 2D Texture Mapping
  glDisable(GL_DEPTH_TEST);         // Disable Depth Testing
  glBlendFunc(GL_SRC_ALPHA,GL_ONE);       // Set Blending Mode
  glEnable(GL_BLEND);           // Enable Blending
  glBindTexture(GL_TEXTURE_2D,BlurTexture);     // Bind To The Blur Texture
  ViewOrtho();              // Switch To An Ortho View

  alphainc = alpha / times; 
  glBegin(GL_QUADS);            // Begin Drawing Quads
  for (int num = 0;num < times;num++)     // Number Of Times To Render Blur
  {
    glColor4f(1.0f, 1.0f, 1.0f, alpha);   // Set The Alpha Value (Starts At 0.2)
    glTexCoord2f(0+spost,1-spost);      // Texture Coordinate (   0,   1 )
    glVertex2f(0,0);        // First Vertex   (   0,   0 )

    glTexCoord2f(0+spost,0+spost);      // Texture Coordinate (   0,   0 )
    glVertex2f(0,480);        // Second Vertex  (   0, 480 )

    glTexCoord2f(1-spost,0+spost);      // Texture Coordinate (   1,   0 )
    glVertex2f(640,480);        // Third Vertex   ( 640, 480 )

    glTexCoord2f(1-spost,1-spost);      // Texture Coordinate (   1,   1 )
    glVertex2f(640,0);        // Fourth Vertex  ( 640,   0 )

    spost += inc;         // Gradually Increase spost (Zooming Closer To Texture Center)
    alpha = alpha - alphainc;     // Gradually Decrease alpha (Gradually Fading Image Out)
  }
  glEnd();              // Done Drawing Quads

  ViewPerspective();            // Switch To A Perspective View

  glEnable(GL_DEPTH_TEST);          // Enable Depth Testing
  glDisable(GL_TEXTURE_2D);         // Disable 2D Texture Mapping
  glDisable(GL_BLEND);            // Disable Blending
  glBindTexture(GL_TEXTURE_2D,0);         // Unbind The Blur Texture
}

void Draw (void)              // Draw The Scene
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.5);        // Set The Clear Color To Black
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    // Clear Screen And Depth Buffer
  glLoadIdentity();           // Reset The View
  RenderToTexture();            // Render To A Texture
  lv.display();             // Draw Our Helix
  DrawBlur(25,0.02f);           // Draw The Blur Effect
  glFlush ();             // Flush The GL Rendering Pipeline
}

