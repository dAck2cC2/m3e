#if TEST_EGL_GL
void hello_triangle(void)
{
        GLfloat vertices[] = {
            0.0f, 0.5f, 0.0f, -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f,
        };

        // Set the viewport
        glViewport(0, 0, screenWidth, screenHeight);

        // Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // Use the program object
        //glUseProgram(mProgram);

        // Load the vertex data
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
        glEnableVertexAttribArray(0);

        glDrawArrays(GL_TRIANGLES, 0, 3);
}
#endif // TEST_EGL_GL

void example_hello_text(void)
{
    ClearBackground(RAYWHITE);

    // TODO: Draw everything that requires to be drawn at this point:
            
    DrawText("Congrats! You created your first window!", 190, 200, 20, YELLOW);  // Example
}

void sharps_basic_sharps(void)
{
    ClearBackground(RAYWHITE);

    //DrawText("some basic shapes available on raylib", 20, 20, 20, DARKGRAY);

    DrawCircle(screenWidth/4, 120, 35, DARKBLUE);

    DrawRectangle(screenWidth/4*2 - 60, 100, 120, 60, RED);
    DrawRectangleLines(screenWidth/4*2 - 40, 320, 80, 60, ORANGE);  // NOTE: Uses QUADS internally, not lines
    DrawRectangleGradientH(screenWidth/4*2 - 90, 170, 180, 130, MAROON, GOLD);

    DrawTriangle((Vector2){screenWidth/4*3, 80},
                 (Vector2){screenWidth/4*3 - 60, 150},
                 (Vector2){screenWidth/4*3 + 60, 150}, VIOLET);

    DrawPoly((Vector2){screenWidth/4*3, 320}, 6, 80, 0, BROWN);

    DrawCircleGradient(screenWidth/4, 220, 60, GREEN, SKYBLUE);

    // NOTE: We draw all LINES based shapes together to optimize internal drawing,
    // this way, all LINES are rendered in a single draw pass
    DrawLine(18, 42, screenWidth - 18, 42, BLACK);
    DrawCircleLines(screenWidth/4, 340, 80, DARKBLUE);
    DrawTriangleLines((Vector2){screenWidth/4*3, 160},
                      (Vector2){screenWidth/4*3 - 20, 230},
                      (Vector2){screenWidth/4*3 + 20, 230}, DARKBLUE);

}
