#include "Core/Application.h"
#include "Assets/Font.h"

#define SCALE 300.f
#define F_PI 3.14159f

#define SIN_COLOR { 255, 0, 0, 255 }
#define COS_COLOR { 0, 255, 0, 255 }

class Trig : public Ember::Application {
public:
	void OnCreate() {
		font.Initialize(renderer, "ClearSans-Medium.ttf", 32);
	}

	virtual ~Trig() { }

	void OnUserUpdate() {
		window->Update();

		Ember::Vec2 origin = { (float)properties->width / 2, (float)properties->height / 2 };
		Ember::Vec2 mouse = { (float)events->MousePosition().x, (float)events->MousePosition().y };

		Ember::Vec2 angle = mouse - origin;
		angle = angle.Normalize();

		renderer->Clear(background_color);

		renderer->DrawCircle({ (int)origin.x, (int)origin.y }, (int)SCALE, { 255, 255, 255, 255 });
		renderer->LineF({ origin.x - SCALE + 1, origin.y }, { origin.x + SCALE - 1, origin.y }, { 255, 255, 255, 255 });
		renderer->LineF({ origin.x, origin.y - SCALE + 1 }, { origin.x, origin.y + SCALE - 1 }, { 255, 255, 255, 255 });

		renderer->LineF({ origin.x, origin.y }, { origin.x + angle.x * SCALE, origin.y + angle.y * SCALE }, { 255, 255, 255, 255 });
		renderer->LineF({ origin.x + angle.x * SCALE, origin.y + angle.y * SCALE },
			{ origin.x + angle.x * SCALE, origin.y }, SIN_COLOR);
		renderer->LineF({ origin.x, origin.y }, { origin.x + angle.x * SCALE, origin.y }, COS_COLOR);

		text_list = 0;
		render_text("Cos: " + std::to_string(angle.x), COS_COLOR);
		render_text("Sin: " + std::to_string(-angle.y), SIN_COLOR);
		render_text("Tan: " + std::to_string(-angle.y / angle.x));
		render_text("Theta: " + std::to_string(fabs(atan(angle.y / angle.x) * 180.f / F_PI)));

		font.SetPosition((int)(origin.x + (SCALE / 2.f)), (int)(origin.y - (SCALE / 2.f)));
		font.UpdateText("I");
		font.Render();
		font.SetPosition((int)(origin.x - (SCALE / 2.f)), (int)(origin.y - (SCALE / 2.f)));
		font.UpdateText("II");
		font.Render();
		font.SetPosition((int)(origin.x - (SCALE / 2.f)), (int)(origin.y + (SCALE / 2.f)));
		font.UpdateText("III");
		font.Render();
		font.SetPosition((int)(origin.x + (SCALE / 2.f)), (int)(origin.y + (SCALE / 2.f)));
		font.UpdateText("IV");
		font.Render();

		renderer->Show();
	}
	template <typename T>
	void render_text(const T& text, const Ember::Color& color = { 255, 255, 255, 255 }) {
		font.UpdateColor(color);
		font.SetPosition(0, text_list);
		font.UpdateText(text);
		font.Render();
		text_list += font.GetSize().y;
	}

	bool Keyboard(Ember::KeyboardEvents& keyboard) {
		if (keyboard.scancode == Ember::EmberKeyCode::Escape) {
			window->Quit();
			return true;
		}
		return false;
	}

	void UserDefEvent(Ember::Event& event) {
		Ember::EventDispatcher dispatch(&event);
		dispatch.Dispatch<Ember::KeyboardEvents>(EMBER_BIND_FUNC(Keyboard));
	}
private:
	Ember::Color background_color = { 0, 0, 0, 255 };
	Ember::Font font;
	int text_list = 0;
};

int main(int argc, char** argv) {
	Trig trig;
	trig.Initialize("Trig");

	trig.Run();

	return 0;
}
