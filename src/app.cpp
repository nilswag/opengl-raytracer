#include <chrono>
#include <glad/glad.h>
#include <spdlog/spdlog.h>

#include "app.h"

app::app()
	: window(1280, 720, "platformer"), dt(0.0f)
{ }

void app::run()
{
	float timer = 0.0f;
	float sum = 0.0f;
	int count = 0;

	auto last = std::chrono::high_resolution_clock::now();
	while (!window.should_close())
	{
		auto first = std::chrono::high_resolution_clock::now();
		dt = std::chrono::duration<float>(first - last).count();
		last = first;

		timer += dt;
		sum += dt;
		count++;

		if (timer >= 1.0f)
		{
			float avg_dt = sum / count;
			float avg_fps = 1.0f / avg_dt;
			spdlog::info("Avg fps: {:<6.1f} | Avg dt: {:.2f}ms", avg_fps, avg_dt * 1e3);

			sum = 0.0f;
			count = 0;
			timer -= 1.0f;
		}

		float color [4] = { 0 };
		glClearNamedFramebufferfv(0, GL_COLOR, 0, color);

		window.swap_buffers();
		window.poll_events();
	}
}