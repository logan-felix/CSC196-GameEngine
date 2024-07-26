#include "Shield.h"
#include "Player.h"
#include "Engine.h"

void Shield::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Player")
	{
		if (!dynamic_cast<Player*>(actor)->GetShielded())
		{
			g_engine.GetAudioSFX().PlaySound("power_up.wav");
			dynamic_cast<Player*>(actor)->SetShield(true);
			m_destroyed = true;
		}
	}
}