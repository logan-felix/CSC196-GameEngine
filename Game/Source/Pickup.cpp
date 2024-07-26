#include "Pickup.h"
#include "Player.h"
#include "Engine.h"

void Pickup::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Player")
	{
		g_engine.GetAudioSFX().PlaySound("power_up.wav");
		dynamic_cast<Player*>(actor)->SetFireModifier(0.01f);
		dynamic_cast<Player*>(actor)->SetFireModTimer(5);
		m_destroyed = true;
	}
}
