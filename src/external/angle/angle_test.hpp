
#ifndef ANGLE_TEST_CLASSS_H
#define ANGLE_TEST_CLASSS_H

#include <list>
#include <memory>
#include <stdint.h>
#include <string>

#include <EGL/egl.h>
#include <EGL/eglext.h>

#include "NativeWindow/NativeWindow.h"

#include <cmath>
#include <algorithm>
#include <vector>

#include "Matrix.h"
#include "random_utils.h"
#include "shader_utils.h"

#include <utils/RefBase.h>

using namespace android;

namespace angle {
	class MultiWindowSample : public RefBase
	{
	public:
		MultiWindowSample(sp<NativeWindow> rootWindow, EGLDisplay display, EGLConfig config, EGLSurface surface, EGLContext context)
			: mRootWindow(rootWindow), mDisplay(display), mConfig(config), mSurface(surface), mContext(context)
		{};

		bool initialize()
		{
			const std::string vs =
				R"(attribute vec4 vPosition;
            void main()
            {
                gl_Position = vPosition;
            })";

			const std::string fs =
				R"(precision mediump float;
            void main()
            {
                gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
            })";

			mProgram = CompileProgram(vs, fs);
			if (!mProgram)
			{
				return false;
			}

			// Set an initial rotation
			mRotation = 45.0f;

			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

			window rootWindow;
			rootWindow.osWindow = mRootWindow;
			rootWindow.surface = mSurface;
			rootWindow.context = mContext;
			mWindows.push_back(rootWindow);

			const size_t numWindows = 5;
			for (size_t i = 1; i < numWindows; i++)
			{
				window window;

				window.osWindow = CreateNativeWindow();
				if (!window.osWindow->initialize("MultiWindow", 256, 256))
				{
					return false;
				}

				window.surface = eglCreateWindowSurface(mDisplay, mConfig, window.osWindow->getNativeWindow(), nullptr);
				if (window.surface == EGL_NO_SURFACE)
				{
					return false;
				}

				const EGLint attribsContext[] = {
					EGL_CONTEXT_MAJOR_VERSION_KHR, 2,
					EGL_NONE
				};
				window.context = eglCreateContext(mDisplay, mConfig, NULL, attribsContext);
				if (window.surface == EGL_NO_CONTEXT)
				{
					return false;
				}


				window.osWindow->setVisible(true);

				mWindows.push_back(window);
			}

			int baseX = rootWindow.osWindow->getX();
			int baseY = rootWindow.osWindow->getY();
			for (auto &window : mWindows)
			{
				int x = baseX + mRNG.randomIntBetween(0, 512);
				int y = baseY + mRNG.randomIntBetween(0, 512);
				int width = mRNG.randomIntBetween(128, 512);
				int height = mRNG.randomIntBetween(128, 512);
				window.osWindow->setPosition(x, y);
				window.osWindow->resize(width, height);
			}

			return true;
		}

		void step()
		{
			for (auto &window : mWindows)
			{
				window.osWindow->messageLoop();
			}
		}
		
		void draw()
		{
			sp<NativeWindow> rootWindow = mWindows[0].osWindow;
			int left = rootWindow->getX();
			int right = rootWindow->getX() + rootWindow->getWidth();
			int top = rootWindow->getY();
			int bottom = rootWindow->getY() + rootWindow->getHeight();

			for (auto &windowRecord : mWindows)
			{
				sp<NativeWindow> window = windowRecord.osWindow;
				left = std::min(left, window->getX());
				right = std::max(right, window->getX() + window->getWidth());
				top = std::min(top, window->getY());
				bottom = std::max(bottom, window->getY() + window->getHeight());
			}

			float midX = (left + right) * 0.5f;
			float midY = (top + bottom) * 0.5f;

			Matrix4 modelMatrix = Matrix4::translate(Vector3(midX, midY, 0.0f)) *
				Matrix4::rotate(mRotation, Vector3(0.0f, 0.0f, 1.0f)) *
				Matrix4::translate(Vector3(-midX, -midY, 0.0f));
			Matrix4 viewMatrix = Matrix4::identity();

			for (auto &windowRecord : mWindows)
			{
				sp<NativeWindow> window = windowRecord.osWindow;
				EGLSurface surface = windowRecord.surface;

				eglMakeCurrent(mDisplay, surface, surface, mContext);
				//eglMakeCurrent(mDsiplay, surface, surface, windowRecord.context);

				Matrix4 orthoMatrix = Matrix4::ortho(static_cast<float>(window->getX()), static_cast<float>(window->getX() + window->getWidth()),
					static_cast<float>(window->getY() + window->getHeight()), static_cast<float>(window->getY()),
					0.0f, 1.0f);
				Matrix4 mvpMatrix = orthoMatrix * viewMatrix * modelMatrix;

				Vector3 vertices[] =
				{
					Matrix4::transform(mvpMatrix, Vector4(midX, static_cast<float>(top), 0.0f, 1.0f)),
					Matrix4::transform(mvpMatrix, Vector4(static_cast<float>(left), static_cast<float>(bottom), 0.0f, 1.0f)),
					Matrix4::transform(mvpMatrix, Vector4(static_cast<float>(right), static_cast<float>(bottom), 0.0f, 1.0f)),
				};

				// Set the viewport
				glViewport(0, 0, window->getWidth(), window->getHeight());

				// Clear the color buffer
				glClear(GL_COLOR_BUFFER_BIT);

				// Use the program object
				glUseProgram(mProgram);

				// Load the vertex data
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices[0].data());
				glEnableVertexAttribArray(0);

				glDrawArrays(GL_TRIANGLES, 0, 3);

				eglSwapBuffers(mDisplay, surface);
			}
		}
	private:
		// Handle to a program object
		GLuint mProgram;

		// Current rotation
		float mRotation;

		// Window and surface data
		struct window
		{
			sp<NativeWindow> osWindow;
			EGLSurface       surface;
			EGLContext       context;
		};
		std::vector<window> mWindows;

		RNG mRNG;

		sp<NativeWindow> mRootWindow;
		EGLDisplay       mDisplay;
		EGLConfig        mConfig;
		EGLSurface       mSurface;
		EGLContext       mContext;
	};

}; // namespace angle 

#endif // ANGLE_TEST_CLASSS_H
