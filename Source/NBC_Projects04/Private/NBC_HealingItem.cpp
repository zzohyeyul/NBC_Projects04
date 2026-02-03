#include "NBC_HealingItem.h"
#include "NBC_Projects04/NBC_Projects04Character.h"

ANBC_HealingItem::ANBC_HealingItem()
{
	HealAmount = 30;
	ItemType = "Healing";
}

void ANBC_HealingItem::ActivateItem(AActor* Activator)
{
	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (ANBC_Projects04Character* PlayerCharacter = Cast<ANBC_Projects04Character>(Activator))
		{
			PlayerCharacter->AddHealth(HealAmount);
		}
		
		DestroyItem();
	}
}