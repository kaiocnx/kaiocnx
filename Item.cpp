#include "Library.h"
#include "Item.h"
#include "User.h"

char ItemDescription[60][100];
DWORD ItemDescriptionColor[60];
DWORD ItemDescriptionType[60];
DWORD CustomBackground[60];
DWORD CustomForeground[60];

Item::Item()
{
}

Item::~Item()
{
}

void Item::Load()
{
	//--------------------------------------------------
// Itens - Items
//--------------------------------------------------
// Para adicionar novos itens, basta:
// this->Add(<item_group>, <item_index>, <file>, <price*>, <glow*>, {
//									{<effect_id>, <bone>, {<red>, <green>, <blue>}, <size>, <amount>},
//									{<effect_id>, <bone>, {<red>, <green>, <blue>}, <size>, <amount>},
//								}*, <others*>);
// item_group -> Grupo do item
// item_index -> ID do item
// file -> Nome do arquivo
// price -> Preço do item (-1 para preço padrão)
// effect_id -> ID do efeito
// bone -> ID do osso que será aplicado o efeito
// red/green/blue -> Cor do efeito
// size -> Tamanho do efeito
// amount -> Quantidade de vezes que o efeito será repetido
// others:
// - item_group == bow/crossbow -> ID do efeito das skills do bows/crossbow (somente para Type bow/crossbow) (1 ~ 9)
// - item_group == wing -> Classe que será destinada a asa (0: wizard, 1: knight, 2: elf, 3: gladiator, 4: lord)
// * optional parameter

// Armas, escudos y bows
	this->Add(Ring, 32);						// Ring of Christmas

	this->Add(Axe, 50);							// Guardian Axe
	this->Add(Mace, 50);						// Mace of King
	this->Add(Scepter, 51);						// HolyAngel Scepter
	this->Add(Scepter, 52, 2000000000,			// Awakening Soul Scepter
		{
		{1452, 2,  {1.00f, 1.00f, 1.00f}, 1.0f,  1},
		{1452, 2,  {1.00f, 0.02f, 0.01f}, 2.0f,  1},
		{1452, 2,  {1.00f, 0.02f, 0.01f}, 2.0f,  1},
		{1452, 2,  {1.00f, 0.85f, 0.36f}, 0.1f,  1},
		{1452, 5,  {0.50f, 0.50f, 0.50f}, 0.5f,  1},
		{1452, 7,  {0.50f, 0.50f, 0.50f}, 0.5f,  1},
		{1452, 8,  {1.00f, 1.00f, 1.00f}, 0.25f, 1},
		{1452, 11, {1.00f, 1.00f, 1.00f}, 0.25f, 1},
		{1452, 21, {1.00f, 1.00f, 1.00f}, 0.25f, 1},
		{1452, 22, {1.00f, 1.00f, 1.00f}, 0.25f, 1},
		{1452, 23, {1.00f, 1.00f, 1.00f}, 0.25f, 1},
		{1452, 9,  {1.00f, 1.00f, 1.00f}, 0.5f,  1},
		{1452, 10, {1.00f, 1.00f, 1.00f}, 0.5f,  1},
		{1452, 12, {1.00f, 1.00f, 1.00f}, 0.5f,  1},
		{1452, 13, {1.00f, 1.00f, 1.00f}, 0.5f,  1},
		{1452, 14, {1.00f, 1.00f, 1.00f}, 0.5f,  1},
		{1452, 15, {1.00f, 1.00f, 1.00f}, 0.5f,  1},
		{1452, 16, {1.00f, 1.00f, 1.00f}, 0.5f,  1}
		});
	this->Add(Mace, 53);						// Guardian Mace
	this->Add(Mace, 54);						// Christmas Mace

	this->Add(Bow, 50, -1,						// HolyAngel Bow
		{
		{1452, 2,  {0.00f, 0.68f, 1.00f}, 2.0f, 1},
		{1452, 4,  {0.00f, 0.68f, 1.00f}, 2.0f, 1},
		{1452, 5,  {0.00f, 0.68f, 1.00f}, 2.0f, 1},
		{1452, 7,  {0.00f, 0.68f, 1.00f}, 2.0f, 1},
		{1452, 12, {0.00f, 0.68f, 1.00f}, 2.0f, 1},
		{1452, 17, {0.00f, 0.68f, 1.00f}, 2.0f, 1},
		{1452, 2,  {1.00f, 1.00f, 1.00f}, 0.5f, 1},
		{1452, 4,  {1.00f, 1.00f, 1.00f}, 0.5f, 1},
		{1452, 5,  {1.00f, 1.00f, 1.00f}, 0.5f, 1},
		{1452, 7,  {1.00f, 1.00f, 1.00f}, 0.5f, 1}
		}, 9);
	this->Add(Bow, 51, -1,						// Awakening Soul Bow
		{
		{1452, 8,  {0.72f, 0.02f, 0.01f}, 0.8f, 1},
		{1452, 9,  {0.72f, 0.02f, 0.01f}, 1.0f, 1},
		{1452, 18, {0.72f, 0.02f, 0.01f}, 1.0f, 1},
		{1452, 49, {0.72f, 0.02f, 0.01f}, 1.0f, 1},
		{1452, 50, {0.72f, 0.02f, 0.01f}, 1.0f, 1},
		{1452, 51, {0.72f, 0.02f, 0.01f}, 1.0f, 1},
		{1452, 52, {0.72f, 0.02f, 0.01f}, 1.0f, 1},
		{1452, 53, {0.72f, 0.02f, 0.01f}, 1.0f, 1},
		{1452, 54, {0.72f, 0.02f, 0.01f}, 1.0f, 1},
		{1452, 62, {0.72f, 0.02f, 0.01f}, 0.5f, 1},
		{1452, 26, {0.72f, 0.02f, 0.01f}, 0.5f, 1},
		{1452, 27, {0.72f, 0.02f, 0.01f}, 1.0f, 1},
		{1452, 36, {0.72f, 0.02f, 0.01f}, 1.0f, 1},
		{1452, 55, {0.72f, 0.02f, 0.01f}, 1.0f, 1},
		{1452, 56, {0.72f, 0.02f, 0.01f}, 1.0f, 1},
		{1452, 57, {0.72f, 0.02f, 0.01f}, 1.0f, 1},
		{1452, 58, {0.72f, 0.02f, 0.01f}, 1.0f, 1},
		{1452, 59, {0.72f, 0.02f, 0.01f}, 1.0f, 1},
		{1452, 60, {0.72f, 0.02f, 0.01f}, 1.0f, 1},
		{1452, 61, {0.72f, 0.02f, 0.01f}, 1.0f, 1},
		{1452, 63, {0.72f, 0.02f, 0.01f}, 0.5f, 1},
		{1452, 16, {0.72f, 0.02f, 0.01f}, 1.5f, 1},
		{1452, 17, {0.72f, 0.02f, 0.01f}, 1.5f, 1},
		{1452, 28, {0.72f, 0.02f, 0.01f}, 1.5f, 1},
		{1452, 29, {0.72f, 0.02f, 0.01f}, 1.5f, 1},
		{1452, 19, {1.00f, 0.95f, 0.73f}, 1.3f, 1},
		{1452, 19, {1.00f, 0.95f, 0.73f}, 0.5f, 1},
		{1452, 37, {1.00f, 0.95f, 0.73f}, 1.3f, 1},
		{1452, 37, {1.00f, 0.95f, 0.73f}, 0.5f, 1},
		{1452, 10, {1.00f, 0.28f, 0.16f}, 0.5f, 1},
		{1452, 11, {1.00f, 0.28f, 0.16f}, 0.5f, 1},
		{1452, 12, {1.00f, 0.28f, 0.16f}, 0.5f, 1},
		{1452, 13, {1.00f, 0.28f, 0.16f}, 0.5f, 1},
		{1452, 14, {1.00f, 0.28f, 0.16f}, 0.5f, 1},
		{1452, 15, {1.00f, 0.28f, 0.16f}, 0.5f, 1},
		{1452, 30, {1.00f, 0.28f, 0.16f}, 0.5f, 1},
		{1452, 31, {1.00f, 0.28f, 0.16f}, 0.5f, 1},
		{1452, 32, {1.00f, 0.28f, 0.16f}, 0.5f, 1},
		{1452, 33, {1.00f, 0.28f, 0.16f}, 0.5f, 1},
		{1452, 34, {1.00f, 0.28f, 0.16f}, 0.5f, 1},
		{1452, 35, {1.00f, 0.28f, 0.16f}, 0.5f, 1}
		}, 9);
	this->Add(Bow, 52, -1,						// Guardian Bow
		{
		{1452, 1,	{1.00f, 0.50f, 0.50f}, 0.5f,	1},
		{1452, 5,	{0.50f, 0.50f, 0.50f}, 0.5f,	1},
		{1452, 5,	{1.00f, 0.00f, 0.00f}, 1.5f,	1},
		{1452, 13,	{1.00f, 0.50f, 0.50f}, 0.3f,	1},
		{1452, 14,	{1.00f, 0.50f, 0.50f}, 0.3f,	1},
		{1452, 15,	{1.00f, 0.50f, 0.50f}, 0.2f,	1},
		{1452, 16,	{1.00f, 0.50f, 0.50f}, 0.2f,	1},
		{1452, 17,	{1.00f, 0.50f, 0.50f}, 0.15f,	1},
		{1452, 18,	{1.00f, 0.50f, 0.50f}, 0.15f,	1},
		{1452, 19,	{1.00f, 0.50f, 0.50f}, 0.3f,	1},
		{1452, 20,	{1.00f, 0.50f, 0.50f}, 0.3f,	1}
		}, 9);
	this->Add(Crossbow, 53, -1, {}, 9);			// Guardian CrossBow
	this->Add(Bow, 54, -1, {}, 9);				// Halloween Bow
	this->Add(Bow, 55, -1, {}, 9);				// Christmas Bow

	this->Add(Blade, 50);						// HolyAngel Magic Blade
	this->Add(Sword, 51);						// HolyAngel Sword
	this->Add(Blade, 52, 2000000000,			// Awakening Magic Blade
		{
		{1452, 1,  {1.00f, 0.28f, 0.16f}, 0.5f, 1},
		{1452, 2,  {1.00f, 0.28f, 0.16f}, 0.5f, 1},
		{1452, 3,  {1.00f, 0.28f, 0.16f}, 0.5f, 1},
		{1452, 4,  {1.00f, 0.28f, 0.16f}, 0.5f, 1},
		{1452, 5,  {1.00f, 0.28f, 0.16f}, 0.5f, 1},
		{1452, 6,  {1.00f, 0.28f, 0.16f}, 0.5f, 1},
		{1452, 7,  {1.00f, 0.28f, 0.16f}, 0.5f, 1},
		{1452, 8,  {1.00f, 0.28f, 0.16f}, 0.5f, 1},
		{1452, 9,  {1.00f, 0.28f, 0.16f}, 0.5f, 1},
		{1452, 10, {1.00f, 0.28f, 0.16f}, 0.5f, 1},
		{1452, 11, {0.72f, 0.02f, 0.01f}, 0.8f, 1},
		{1452, 12, {0.72f, 0.02f, 0.01f}, 0.9f, 1},
		{1452, 13, {0.72f, 0.02f, 0.01f}, 1.0f, 1},
		{1452, 14, {0.72f, 0.02f, 0.01f}, 1.1f, 1},
		{1452, 15, {0.72f, 0.02f, 0.01f}, 1.2f, 1},
		{1452, 16, {0.72f, 0.02f, 0.01f}, 1.3f, 1},
		{1452, 17, {0.72f, 0.02f, 0.01f}, 1.3f, 1},
		{1452, 18, {0.72f, 0.02f, 0.01f}, 1.3f, 1},
		{1452, 19, {0.72f, 0.02f, 0.01f}, 1.3f, 1},
		{1452, 20, {0.72f, 0.02f, 0.01f}, 1.3f, 1},
		{1452, 21, {0.72f, 0.02f, 0.01f}, 1.3f, 1},
		{1452, 22, {0.72f, 0.02f, 0.01f}, 1.3f, 1},
		{1452, 23, {0.72f, 0.02f, 0.01f}, 1.3f, 1},
		{1452, 24, {0.72f, 0.02f, 0.01f}, 1.3f, 1},
		{1452, 25, {0.72f, 0.02f, 0.01f}, 1.3f, 1},
		{1452, 26, {0.72f, 0.02f, 0.01f}, 1.3f, 1},
		{1452, 27, {0.72f, 0.02f, 0.01f}, 1.3f, 1}
		});
	this->Add(Sword, 53, 2000000000,			// Awakening Soul Sword
		{
		{1452, 1,  {1.00f, 1.00f, 1.00f}, 0.5f,  1},
		{1452, 2,  {1.00f, 1.00f, 1.00f}, 0.5f,  1},
		{1452, 3,  {1.00f, 1.00f, 1.00f}, 0.5f,  1},
		{1452, 4,  {1.00f, 1.00f, 1.00f}, 0.25f, 1},
		{1452, 5,  {1.00f, 1.00f, 1.00f}, 0.5f,  1},
		{1452, 6,  {1.00f, 1.00f, 1.00f}, 0.25f, 1},
		{1452, 8,  {1.00f, 0.02f, 0.01f}, 0.5f,  1},
		{1452, 8,  {1.00f, 0.02f, 0.01f}, 0.5f,  1},
		{1452, 9,  {0.81f, 0.64f, 0.48f}, 0.65f, 1},
		{1452, 10, {0.81f, 0.64f, 0.48f}, 0.65f, 1},
		{1452, 11, {0.81f, 0.64f, 0.48f}, 0.65f, 1},
		{1452, 12, {0.81f, 0.64f, 0.48f}, 0.65f, 1},
		{1452, 13, {0.81f, 0.64f, 0.48f}, 0.65f, 1},
		{1452, 14, {0.81f, 0.64f, 0.48f}, 0.65f, 1},
		{1452, 15, {0.81f, 0.64f, 0.48f}, 0.65f, 1},
		{1452, 16, {0.81f, 0.64f, 0.48f}, 0.65f, 1},
		{1452, 17, {0.81f, 0.64f, 0.48f}, 0.65f, 1},
		{1452, 18, {0.81f, 0.64f, 0.48f}, 0.65f, 1},
		{1452, 19, {0.81f, 0.64f, 0.48f}, 0.65f, 1},
		{1452, 20, {0.81f, 0.64f, 0.48f}, 0.65f, 1},
		{1452, 21, {0.81f, 0.64f, 0.48f}, 0.65f, 1},
		{1452, 22, {0.81f, 0.64f, 0.48f}, 0.65f, 1},
		{1452, 23, {0.81f, 0.64f, 0.48f}, 0.65f, 1},
		{1452, 24, {0.81f, 0.64f, 0.48f}, 0.65f, 1},
		{1452, 25, {0.81f, 0.64f, 0.48f}, 0.65f, 1},
		{1452, 26, {0.81f, 0.64f, 0.48f}, 0.5f,  1},
		{1452, 27, {0.81f, 0.64f, 0.48f}, 0.65f, 1},
		{1452, 28, {0.81f, 0.64f, 0.48f}, 0.65f, 1},
		{1452, 29, {0.81f, 0.64f, 0.48f}, 0.65f, 1},
		{1452, 30, {0.81f, 0.64f, 0.48f}, 0.65f, 1},
		{1452, 31, {0.81f, 0.64f, 0.48f}, 0.65f, 1},
		{1452, 32, {0.81f, 0.64f, 0.48f}, 0.65f, 1},
		{1452, 33, {0.81f, 0.64f, 0.48f}, 0.65f, 1},
		{1452, 34, {0.81f, 0.64f, 0.48f}, 0.65f, 1},
		{1452, 35, {0.81f, 0.64f, 0.48f}, 0.65f, 1},
		{1452, 36, {0.81f, 0.64f, 0.48f}, 0.65f, 1},
		{1452, 37, {0.81f, 0.64f, 0.48f}, 0.65f, 1},
		{1452, 38, {0.81f, 0.64f, 0.48f}, 0.65f, 1},
		{1452, 39, {0.81f, 0.64f, 0.48f}, 0.65f, 1},
		{1452, 40, {0.81f, 0.64f, 0.48f}, 0.65f, 1},
		{1452, 41, {0.81f, 0.64f, 0.48f}, 0.65f, 1},
		{1452, 42, {0.81f, 0.64f, 0.48f}, 0.65f, 1}
		});
	this->Add(Sword, 54, 2000000000,			// Guardian Sword
		{
		{1452, 8, 	{1.00f, 0.00f, 0.00f}, 1.5f,  1},
		{1452, 8, 	{0.50f, 0.50f, 0.50f}, 0.5f,  1},
		{1452, 9, 	{1.00f, 0.50f, 0.50f}, 0.2f,  1},
		{1452, 10,  {1.00f, 0.50f, 0.50f}, 0.2f,  1},
		{1452, 11,  {1.00f, 0.50f, 0.50f}, 0.3f,  1},
		{1452, 12,  {1.00f, 0.50f, 0.50f}, 0.3f,  1},
		{1452, 13,  {1.00f, 0.50f, 0.50f}, 0.3f,  1},
		{1452, 14,  {1.00f, 0.50f, 0.50f}, 0.3f,  1},
		{1452, 15,  {1.00f, 0.50f, 0.50f}, 0.3f,  1},
		{1452, 16,  {1.00f, 0.50f, 0.50f}, 0.3f,  1},
		{1452, 17,  {1.00f, 0.50f, 0.50f}, 0.3f,  1},
		{1452, 18,  {1.00f, 0.50f, 0.50f}, 0.3f,  1},
		{1452, 19,  {1.00f, 0.50f, 0.50f}, 0.2f,  1},
		{1452, 20,  {1.00f, 0.50f, 0.50f}, 0.2f,  1},
		{1452, 21,  {1.00f, 0.50f, 0.50f}, 0.15f, 1},
		{1452, 22,  {1.00f, 0.50f, 0.50f}, 0.15f, 1}
		});
	this->Add(Sword, 55);						// Halloween Sword
	this->Add(Sword, 56);						// Christmas Sword

	this->Add(Staff, 50);						// HolyAngel Staff
	this->Add(Staff, 51, 2000000000,			// Awakening Soul Staff
		{
		{1452, 2,  {0.50f, 0.50f, 0.50f}, 0.8f, 1},
		{1452, 2,  {0.89f, 0.47f, 0.27f}, 1.5f, 1},
		{1452, 2,  {0.89f, 0.47f, 0.27f}, 1.5f, 1},
		{1452, 2,  {1.00f, 0.92f, 0.53f}, 0.45, 1},
		{1452, 3,  {0.99f, 0.50f, 0.25f}, 1.0f, 1},
		{1452, 3,  {0.99f, 0.50f, 0.25f}, 0.2f, 1},
		{1452, 4,  {0.99f, 0.50f, 0.25f}, 1.0f, 1},
		{1452, 4,  {0.99f, 0.50f, 0.25f}, 0.2f, 1},
		{1452, 5,  {0.99f, 0.50f, 0.25f}, 0.2f, 1},
		{1452, 5,  {0.99f, 0.50f, 0.25f}, 0.2f, 1},
		{1452, 6,  {0.99f, 0.50f, 0.25f}, 0.2f, 1},
		{1452, 6,  {0.99f, 0.50f, 0.25f}, 0.2f, 1},
		{1452, 7,  {0.99f, 0.50f, 0.25f}, 0.2f, 1},
		{1452, 7,  {0.99f, 0.50f, 0.25f}, 0.2f, 1},
		{1452, 8,  {0.99f, 0.50f, 0.25f}, 0.2f, 1},
		{1452, 8,  {0.99f, 0.50f, 0.25f}, 0.2f, 1},
		{1452, 9,  {1.00f, 0.27f, 0.00f}, 0.8f, 1},
		{1452, 10, {1.00f, 0.27f, 0.00f}, 0.8f, 1},
		{1452, 11, {1.00f, 0.27f, 0.00f}, 0.5f, 1},
		{1452, 11, {1.00f, 0.27f, 0.00f}, 0.25f, 1},
		{1452, 12, {1.00f, 0.27f, 0.00f}, 0.5f, 1},
		{1452, 12, {1.00f, 0.27f, 0.00f}, 0.25f, 1}
		});
	this->Add(Staff, 52);						// Guardian Staff
	this->Add(Staff, 53);						// Halloween Staff
	this->Add(Staff, 54);						// Christmas Staff

	this->Add(Shield, 50);						// Guardian Shield SM
	this->Add(Shield, 51);						// Halloween Shield
	this->Add(Shield, 52);						// Christmas Shield

	//Items 2020 (Armas) ================================
	//Shields
	this->Add(Shield, 53);						// Shield
	this->Add(Shield, 54);						// Shield
	this->Add(Shield, 55);						// Shield
	this->Add(Shield, 56);						// Shield
	this->Add(Shield, 57);						// Shield

	//Staffs
	this->Add(Staff, 55);						// Staff
	this->Add(Staff, 56);						// Staff
	this->Add(Staff, 57);						// Staff

	this->Add(Scepter, 55);						// Scepter
	this->Add(Scepter, 56);						// Scepter

	//Swords
	this->Add(Sword, 57);						// Sword
	this->Add(Sword, 58);						// Sword
	this->Add(Sword, 59);						// Sword
	this->Add(Sword, 60);						// Sword
	//===================================================

	// Boxs
	this->Add(Box, 50);			//Box of Yelow
	this->Add(Box, 51);			//Box of Red
	this->Add(Box, 52);			//Box of Green
	this->Add(Box, 53);			//Box of Blue
	this->Add(Box, 54);			//Box of Pink
	this->Add(Box, 55);			//Box of Halloween

	// Cofres de Zen
	this->Add(Box, 56);			//Cofre de Bronce
	this->Add(Box, 57);			//Cofre de Plata
	this->Add(Box, 58);			//Cofre de Oro

	// Entrada Navidad
	this->Add(Box, 59);			//Invitation to Santa Village
	this->Add(Box, 60);			//Box of Christmas

	// Box Especiales
	this->Add(Box, 61);			//Box of VIP
	this->Add(Box, 62);			//Box oF Wing

	// Jewels
	this->Add(Jewel, 160);		//Lucky Clover
	this->Add(Jewel, 161);		//Jewel of Blow
	this->Add(Jewel, 162);		//Jewel of Power
	this->Add(Jewel, 163);		//Jewel of Ruin
	this->Add(Jewel, 164);		//Crystal of Change
	this->Add(Jewel, 165);		//Jewel of Special
	this->Add(Jewel, 166);		//Jewel of Ancient 1
	this->Add(Jewel, 167);		//Jewel of Ancient 2

	// Sets
	this->Add(Helm, 50);		// Set Ashcrow BK
	this->Add(Armor, 50);		// Set Ashcrow BK
	this->Add(Pants, 50);		// Set Ashcrow BK
	this->Add(Gloves, 50);		// Set Ashcrow BK
	this->Add(Boots, 50);		// Set Ashcrow BK

	this->Add(Helm, 51);		// Set Eclipse SM
	this->Add(Armor, 51);		// Set Eclipse SM
	this->Add(Pants, 51);		// Set Eclipse SM
	this->Add(Gloves, 51);		// Set Eclipse SM
	this->Add(Boots, 51);		// Set Eclipse SM

	this->Add(Helm, 52);		// Set Iris ELF
	this->Add(Armor, 52);		// Set Iris ELF
	this->Add(Pants, 52);		// Set Iris ELF
	this->Add(Gloves, 52);		// Set Iris ELF
	this->Add(Boots, 52);		// Set Iris ELF

	this->Add(Armor, 53);		// Set Valiant MG
	this->Add(Pants, 53);		// Set Valiant MG
	this->Add(Gloves, 53);		// Set Valiant MG
	this->Add(Boots, 53);		// Set Valiant MG

	this->Add(Helm, 54);		// Set Glorious DL
	this->Add(Armor, 54);		// Set Glorious DL
	this->Add(Pants, 54);		// Set Glorious DL
	this->Add(Gloves, 54);		// Set Glorious DL
	this->Add(Boots, 54);		// Set Glorious DL

	this->Add(Helm, 55);		// Set Titan BK
	this->Add(Armor, 55);		// Set Titan BK
	this->Add(Pants, 55);		// Set Titan BK
	this->Add(Gloves, 55);		// Set Titan BK
	this->Add(Boots, 55);		// Set Titan BK

	this->Add(Helm, 56);		// Set Brave BK
	this->Add(Armor, 56);		// Set Brave BK
	this->Add(Pants, 56);		// Set Brave BK
	this->Add(Gloves, 56);		// Set Brave BK
	this->Add(Boots, 56);		// Set Brave BK

	this->Add(Armor, 57);		// Set Phantom MG
	this->Add(Pants, 57);		// Set Phantom MG
	this->Add(Gloves, 57);		// Set Phantom MG
	this->Add(Boots, 57);		// Set Phantom MG

	this->Add(Armor, 58);		// Set Destroy MG
	this->Add(Pants, 58);		// Set Destroy MG
	this->Add(Gloves, 58);		// Set Destroy MG
	this->Add(Boots, 58);		// Set Destroy MG

	this->Add(Helm, 59);		// Set Seraphim ELF
	this->Add(Armor, 59);		// Set Seraphim ELF
	this->Add(Pants, 59);		// Set Seraphim ELF
	this->Add(Gloves, 59);		// Set Seraphim ELF
	this->Add(Boots, 59);		// Set Seraphim ELF

	this->Add(Helm, 60);		// Set Royal DL
	this->Add(Armor, 60);		// Set Royal DL
	this->Add(Pants, 60);		// Set Royal DL
	this->Add(Gloves, 60);		// Set Royal DL
	this->Add(Boots, 60);		// Set Royal DL

	this->Add(Helm, 61);		// Set Hades SM
	this->Add(Armor, 61);		// Set Hades SM
	this->Add(Pants, 61);		// Set Hades SM
	this->Add(Gloves, 61);		// Set Hades SM
	this->Add(Boots, 61);		// Set Hades SM

	this->Add(Helm, 62);		// Set Queen ELF
	this->Add(Armor, 62);		// Set Queen ELF
	this->Add(Pants, 62);		// Set Queen ELF
	this->Add(Gloves, 62);		// Set Queen ELF
	this->Add(Boots, 62);		// Set Queen ELF

	this->Add(Helm, 63);		// Set Hollow (Halloween)
	this->Add(Armor, 63);		// Set Hollow (Halloween)
	this->Add(Pants, 63);		// Set Hollow (Halloween)
	this->Add(Gloves, 63);		// Set Hollow (Halloween)
	this->Add(Boots, 63);		// Set Hollow (Halloween)

	this->Add(Helm, 64);		// Set Hollow Lady (Halloween)
	this->Add(Armor, 64);		// Set Hollow Lady (Halloween)
	this->Add(Pants, 64);		// Set Hollow Lady (Halloween)
	this->Add(Gloves, 64);		// Set Hollow Lady (Halloween)
	this->Add(Boots, 64);		// Set Hollow Lady (Halloween)

	this->Add(Helm, 65);		// Set Rudolph (Christmas)
	this->Add(Armor, 65);		// Set Rudolph (Christmas)
	this->Add(Pants, 65);		// Set Rudolph (Christmas)
	this->Add(Gloves, 65);		// Set Rudolph (Christmas)
	this->Add(Boots, 65);		// Set Rudolph (Christmas)

	this->Add(Helm, 66);		// Set Santa Girl (Christmas)
	this->Add(Armor, 66);		// Set Santa Girl (Christmas)
	this->Add(Pants, 66);		// Set Santa Girl (Christmas)
	this->Add(Gloves, 66);		// Set Santa Girl (Christmas)
	this->Add(Boots, 66);		// Set Santa Girl (Christmas)

	this->Add(Helm, 67);		// Set Santa (Christmas)
	this->Add(Armor, 67);		// Set Santa (Christmas)
	this->Add(Pants, 67);		// Set Santa (Christmas)
	this->Add(Gloves, 67);		// Set Santa (Christmas)
	this->Add(Boots, 67);		// Set Santa (Christmas)

	this->Add(Helm, 68);		// Set Awakening Elves
	this->Add(Armor, 68);		// Set Awakening Elves
	this->Add(Pants, 68);		// Set Awakening Elves
	this->Add(Gloves, 68);		// Set Awakening Elves
	this->Add(Boots, 68);		// Set Awakening Elves

	this->Add(Helm, 69);		// Set Awakening Knight
	this->Add(Armor, 69);		// Set Awakening Knight
	this->Add(Pants, 69);		// Set Awakening Knight
	this->Add(Gloves, 69);		// Set Awakening Knight
	this->Add(Boots, 69);		// Set Awakening Knight

	this->Add(Helm, 70);		// Set Awakening Magic
	this->Add(Armor, 70);		// Set Awakening Magic
	this->Add(Pants, 70);		// Set Awakening Magic
	this->Add(Gloves, 70);		// Set Awakening Magic
	this->Add(Boots, 70);		// Set Awakening Magic

	this->Add(Helm, 71);		// Set Frost Soul Elf
	this->Add(Armor, 71);		// Set Frost Soul Elf
	this->Add(Pants, 71);		// Set Frost Soul Elf
	this->Add(Gloves, 71);		// Set Frost Soul Elf
	this->Add(Boots, 71);		// Set Frost Soul Elf

	this->Add(Helm, 72);		// Set Frost Soul Knight
	this->Add(Armor, 72);		// Set Frost Soul Knight
	this->Add(Pants, 72);		// Set Frost Soul Knight
	this->Add(Gloves, 72);		// Set Frost Soul Knight
	this->Add(Boots, 72);		// Set Frost Soul Knight

	this->Add(Helm, 73);		// Set Frost Soul Wizard
	this->Add(Armor, 73);		// Set Frost Soul Wizard
	this->Add(Pants, 73);		// Set Frost Soul Wizard
	this->Add(Gloves, 73);		// Set Frost Soul Wizard
	this->Add(Boots, 73);		// Set Frost Soul Wizard

	// Asas e Capas
	this->Add(Wing, 50, 2000000000, {				//Wing of Storm
		{
		{1452, 7 , {1.0f, 0.4f, 0.0f}, 1.0f, 1},
		{1452, 12, {1.0f, 0.4f, 0.0f}, 1.0f, 1},
		{1452, 12, {1.0f, 0.4f, 0.0f}, 1.0f, 1},
		{1452, 16, {1.0f, 0.4f, 0.0f}, 1.0f, 1},
		{1452, 25, {1.0f, 0.4f, 0.0f}, 1.0f, 1},
		{1452, 33, {1.0f, 0.4f, 0.0f}, 1.0f, 1},
		{1452, 46, {1.0f, 0.4f, 0.0f}, 1.0f, 1},
		{1452, 49, {1.0f, 0.4f, 0.0f}, 1.0f, 1},
		{1452, 50, {1.0f, 0.4f, 0.0f}, 1.0f, 1},
		{1452, 51, {1.0f, 0.4f, 0.0f}, 1.0f, 1},
		{1452, 52, {1.0f, 0.4f, 0.0f}, 1.0f, 1},
		{1452, 60, {1.0f, 0.4f, 0.0f}, 1.0f, 1},
		{1452, 64, {1.0f, 0.4f, 0.0f}, 1.0f, 1},
		{1452, 68, {1.0f, 0.4f, 0.0f}, 1.0f, 1},
		{1452, 76, {1.0f, 0.4f, 0.0f}, 1.0f, 1},
		{1452, 85, {1.0f, 0.4f, 0.0f}, 1.0f, 1},
		{1452, 96, {1.0f, 0.4f, 0.0f}, 1.0f, 1},
		{1452, 98, {1.0f, 0.4f, 0.0f}, 1.0f, 1},
		{1452, 99, {1.0f, 0.4f, 0.0f}, 1.0f, 1},
		{1452, 10, {1.0f, 0.4f, 0.0f}, 1.0f, 1},
		{1452, 10, {1.0f, 0.4f, 0.0f}, 1.0f, 1},
		}
		}, 1);
	this->Add(Wing, 51, 2000000000, {				//Wing of Eternal
		{1452, 5, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 6, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 7, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 9, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 11, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 12, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 13, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 14, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 16, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 20, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 21, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 22, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 23, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 25, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 27, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 28, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 29, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 30, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 32, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 35, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 36, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 37, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 38, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 39, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 40, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 42, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 43, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 44, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 45, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 48, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 49, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 50, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 51, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 53, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 54, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 55, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 56, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 57, {0.0f, 0.2f, 1.0f}, 1.0f, 1},
		{1452, 58, {0.0f, 0.2f, 1.0f}, 1.0f, 1}
		}, 0);
	this->Add(Wing, 52, 2000000000, {				// Wing of Illusion
		{1551, 5,  {1.0f, 0.4f, 0.4f}, 1.0f, 1},
		{1551, 6,  {1.0f, 0.4f, 0.4f}, 1.0f, 1},
		{1551, 7,  {1.0f, 0.4f, 0.4f}, 1.0f, 1},
		{1551, 8,  {1.0f, 0.4f, 0.4f}, 1.0f, 1},
		{1551, 18, {1.0f, 0.4f, 0.4f}, 1.0f, 1},
		{1551, 23, {1.0f, 0.4f, 0.4f}, 1.0f, 1},
		{1551, 24, {1.0f, 0.4f, 0.4f}, 1.0f, 1},
		{1551, 25, {1.0f, 0.4f, 0.4f}, 1.0f, 1},
		{1551, 27, {1.0f, 0.4f, 0.4f}, 1.0f, 1},
		{1551, 37, {1.0f, 0.4f, 0.4f}, 1.0f, 1}
		}, 2);
	this->Add(Wing, 53, 2000000000, {				// Wing of Ruin
		{
		 {1452, 2,  {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 3,  {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 4,  {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 5,  {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 6,  {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 7,  {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 8,  {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 9,  {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 10, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 11, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 12, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 13, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 14, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 15, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 16, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 17, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 18, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 19, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 20, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 21, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 22, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 23, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 24, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 25, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 26, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 27, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 28, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 29, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 30, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 31, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 32, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 34, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 35, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 36, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 37, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 38, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 39, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 40, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 41, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 42, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 43, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 44, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 45, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 46, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 47, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 48, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 49, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 50, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 51, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 52, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 53, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 54, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 55, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 56, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 57, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 58, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 59, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 60, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 61, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 62, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 63, {0.25f, 0.10f, 0.8f}, 1.0f, 1},
		 {1452, 64, {0.25f, 0.10f, 0.8f}, 1.0f, 1}
		}
		}, 3);
	this->Add(Cape, 54, 2000000000, {				// Cape of Emperor
		{}
		}, 4);
	this->Add(Wing, 55, 2000000000, {				// Wing of Fall
		{
		 {1452, 4,  {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		 {1452, 12, {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		 {1452, 20, {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		 {1452, 28, {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		 {1452, 36, {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		 {1452, 44, {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		 {1452, 52, {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		 {1452, 60, {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		 {1452, 4,  {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		 {1452, 12, {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		 {1452, 20, {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		 {1452, 28, {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		 {1452, 36, {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		 {1452, 44, {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		 {1452, 52, {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		 {1452, 60, {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		 {1452, 9,  {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		 {1452, 17, {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		 {1452, 25, {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		 {1452, 33, {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		 {1452, 41, {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		 {1452, 49, {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		 {1452, 57, {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		 {1452, 65, {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		 {1452, 9,  {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		 {1452, 17, {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		 {1452, 25, {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		 {1452, 33, {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		 {1452, 41, {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		 {1452, 49, {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		 {1452, 57, {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		 {1452, 65, {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		 {1452, 72, {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		 {1452, 79, {1.00f, 0.72f, 0.25f}, 1.0f, 1}
		}
		}, 3);
	this->Add(Wing, 56, 2000000000, {				// Wing of Orb
		{
		{1452, 9,  {1.00f, 0.70f, 0.20f}, 1.0f , 1},
		{1452, 23, {1.00f, 0.70f, 0.20f}, 1.0f , 1},
		{1452, 65, {1.00f, 0.70f, 0.20f}, 1.0f , 1},
		{1452, 93, {1.00f, 0.70f, 0.20f}, 1.0f , 1},
		{1452, 38, {1.00f, 0.70f, 0.20f}, 0.7f , 1},
		{1452, 80, {1.00f, 0.70f, 0.20f}, 0.7f , 1},
		{1452, 62, {1.00f, 0.70f, 0.20f}, 0.4f , 1},
		{1452, 6,  {1.00f, 0.70f, 0.20f}, 0.4f , 1},
		{1452, 9,  {1.00f, 0.70f, 0.20f}, 0.6f , 1},
		{1452, 23, {1.00f, 0.70f, 0.20f}, 0.6f , 1},
		{1452, 65, {1.00f, 0.70f, 0.20f}, 0.6f , 1},
		{1452, 93, {1.00f, 0.70f, 0.20f}, 0.6f , 1},
		{1452, 38, {1.00f, 0.70f, 0.20f}, 0.6f , 1},
		{1452, 80, {1.00f, 0.70f, 0.20f}, 0.6f , 1},
		{1452, 7,  {0.20f, 0.20f, 1.00f}, 0.6f , 1},
		{1452, 8,  {0.20f, 0.20f, 1.00f}, 0.6f , 1},
		{1452, 13, {0.20f, 0.20f, 1.00f}, 0.5f , 1},
		{1452, 14, {0.20f, 0.20f, 1.00f}, 0.5f , 1},
		{1452, 15, {0.20f, 0.20f, 1.00f}, 0.5f , 1},
		{1452, 16, {0.20f, 0.20f, 1.00f}, 0.5f , 1},
		{1452, 63, {0.20f, 0.20f, 1.00f}, 0.6f , 1},
		{1452, 64, {0.20f, 0.20f, 1.00f}, 0.5f , 1},
		{1452, 69, {0.20f, 0.20f, 1.00f}, 0.5f , 1},
		{1452, 70, {0.20f, 0.20f, 1.00f}, 0.5f , 1},
		{1452, 71, {0.20f, 0.20f, 1.00f}, 0.5f , 1},
		{1452, 72, {0.20f, 0.20f, 1.00f}, 0.5f , 1},
		{1452, 24, {0.20f, 0.20f, 1.00f}, 0.8f , 1},
		{1452, 26, {0.20f, 0.20f, 1.00f}, 0.3f , 1},
		{1452, 27, {0.20f, 0.20f, 1.00f}, 0.5f , 1},
		{1452, 39, {0.20f, 0.20f, 1.00f}, 0.6f , 1},
		{1452, 36, {0.20f, 0.20f, 1.00f}, 0.6f , 1},
		{1452, 79, {0.20f, 0.20f, 1.00f}, 0.6f , 1},
		{1452, 77, {0.20f, 0.20f, 1.00f}, 0.6f , 1},
		{1452, 89, {0.20f, 0.20f, 1.00f}, 0.8f , 1},
		{1452, 91, {0.20f, 0.20f, 1.00f}, 0.3f , 1},
		{1452, 92, {0.20f, 0.20f, 1.00f}, 0.5f , 1},
		{1452, 42, {1.00f, 0.20f, 1.00f}, 0.6f , 1},
		{1452, 43, {1.00f, 0.20f, 1.00f}, 0.6f , 1},
		{1452, 44, {1.00f, 0.20f, 1.00f}, 0.6f , 1},
		{1452, 45, {1.00f, 0.20f, 1.00f}, 0.6f , 1},
		{1452, 46, {1.00f, 0.20f, 1.00f}, 0.6f , 1},
		{1452, 47, {1.00f, 0.20f, 1.00f}, 0.6f , 1},
		{1452, 48, {1.00f, 0.20f, 1.00f}, 0.6f , 1},
		{1452, 49, {1.00f, 0.20f, 1.00f}, 0.6f , 1},
		{1452, 50, {1.00f, 0.20f, 1.00f}, 0.6f , 1},
		{1452, 51, {1.00f, 0.20f, 1.00f}, 0.6f , 1},
		{1452, 52, {1.00f, 0.20f, 1.00f}, 0.6f , 1},
		{1452, 53, {1.00f, 0.20f, 1.00f}, 0.6f , 1},
		{1452, 54, {1.00f, 0.20f, 1.00f}, 0.6f , 1},
		{1452, 98, {1.00f, 0.20f, 1.00f}, 0.6f , 1},
		{1452, 99, {1.00f, 0.20f, 1.00f}, 0.6f , 1},
		{1452, 100,{1.00f, 0.20f, 1.00f}, 0.6f , 1},
		{1452, 101,{1.00f, 0.20f, 1.00f}, 0.6f , 1},
		{1452, 102,{1.00f, 0.20f, 1.00f}, 0.6f , 1},
		{1452, 103,{1.00f, 0.20f, 1.00f}, 0.6f , 1},
		{1452, 104,{1.00f, 0.20f, 1.00f}, 0.6f , 1},
		{1452, 105,{1.00f, 0.20f, 1.00f}, 0.6f , 1},
		{1452, 106,{1.00f, 0.20f, 1.00f}, 0.6f , 1},
		{1452, 107,{1.00f, 0.20f, 1.00f}, 0.6f , 1},
		{1452, 108,{1.00f, 0.20f, 1.00f}, 0.6f , 1},
		{1452, 109,{1.00f, 0.20f, 1.00f}, 0.6f , 1},
		{1452, 110,{1.00f, 0.20f, 1.00f}, 0.6f , 1},
		{1452, 23, {1.00f, 0.70f, 0.20f}, 0.4f , 1},
		{1452, 38, {1.00f, 0.70f, 0.20f}, 0.25f, 1},
		{1452, 9,  {1.00f, 0.70f, 0.20f}, 0.2f , 1},
		{1452, 65, {1.00f, 0.70f, 0.20f}, 0.2f , 1},
		{1452, 80, {1.00f, 0.70f, 0.20f}, 0.25f, 1},
		{1452, 93, {1.00f, 0.70f, 0.20f}, 0.4f , 1}
		}
		}, 2);
	this->Add(Wing, 57, 2000000000, {				// Wing of Avatar
		{
		{1452, 7,   {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 8,   {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 9,   {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 77,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 78,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 79,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 11,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 12,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 81,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 82,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 17,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 87,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 22,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 23,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 24,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 25,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 92,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 93,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 94,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 95,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 30,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 31,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 32,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 33,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 34,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 35,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 36,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 37,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 38,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 100, {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 101, {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 102, {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 103, {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 104, {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 105, {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 106, {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 107, {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 108, {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 45,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 46,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 47,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 53,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 54,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 55,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 56,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 60,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 61,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 62,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 66,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 67,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 68,  {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 115, {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 116, {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 117, {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 123, {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 124, {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 125, {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 118, {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 130, {1.00f, 0.0f, 0.0f}, 1.0f, 1},
		{1452, 131, {1.00f, 0.0f, 0.0f}, 1.0f, 1}
		}
		}, 1);
	this->Add(Wing, 58, 2000000000, {				// Wing of Heavenly
		{
		{1452, 6,  {1.00f, 0.98f, 0.93}, 1.0f, 1},
		{1452, 9,  {1.00f, 0.98f, 0.93}, 1.0f, 1},
		{1452, 15, {1.00f, 0.98f, 0.93}, 1.0f, 1},
		{1452, 17, {1.00f, 0.98f, 0.93}, 1.0f, 1},
		{1452, 21, {1.00f, 0.98f, 0.93}, 1.0f, 1},
		{1452, 22, {1.00f, 0.98f, 0.93}, 1.0f, 1},
		{1452, 29, {1.00f, 0.98f, 0.93}, 1.0f, 1},
		{1452, 32, {1.00f, 0.98f, 0.93}, 1.0f, 1},
		{1452, 34, {1.00f, 0.98f, 0.93}, 1.0f, 1},
		{1452, 40, {1.00f, 0.98f, 0.93}, 1.0f, 1},
		{1452, 41, {1.00f, 0.98f, 0.93}, 1.0f, 1},
		{1452, 45, {1.00f, 0.98f, 0.93}, 1.0f, 1},
		{1452, 13, {1.00f, 0.98f, 0.93}, 1.0f, 1},
		{1452, 14, {1.00f, 0.98f, 0.93}, 1.0f, 1},
		{1452, 16, {1.00f, 0.98f, 0.93}, 1.0f, 1},
		{1452, 23, {1.00f, 0.98f, 0.93}, 1.0f, 1},
		{1452, 33, {1.00f, 0.98f, 0.93}, 1.0f, 1},
		{1452, 38, {1.00f, 0.98f, 0.93}, 1.0f, 1},
		{1452, 39, {1.00f, 0.98f, 0.93}, 1.0f, 1},
		{1452, 46, {1.00f, 0.98f, 0.93}, 1.0f, 1},
		{1452, 10, {1.00f, 0.98f, 0.93}, 1.0f, 1},
		{1452, 12, {1.00f, 0.98f, 0.93}, 1.0f, 1},
		{1452, 35, {1.00f, 0.98f, 0.93}, 1.0f, 1},
		{1452, 37, {1.00f, 0.98f, 0.93}, 1.0f, 1}
		}
		}, 0);
	this->Add(Cape, 59, 2000000000, {				// Cape of Control
		{
		{1452, 25, {0.32f, 0.88f, 1.00f}, 1.0f, 1},
		{1452, 26, {0.32f, 0.88f, 1.00f}, 1.0f, 1},
		{1452, 27, {0.32f, 0.88f, 1.00f}, 1.0f, 1},
		{1452, 28, {0.32f, 0.88f, 1.00f}, 1.0f, 1},
		{1452, 29, {0.32f, 0.88f, 1.00f}, 1.0f, 1},
		{1452, 30, {0.32f, 0.88f, 1.00f}, 1.0f, 1},
		{1452, 31, {0.32f, 0.88f, 1.00f}, 1.0f, 1},
		{1452, 32, {0.32f, 0.88f, 1.00f}, 1.0f, 1},
		{1452, 33, {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		{1452, 34, {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		{1452, 33, {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		{1452, 34, {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		{1452, 35, {1.00f, 0.72f, 0.25f}, 1.0f, 1},
		{1452, 36, {1.00f, 0.72f, 0.25f}, 1.0f, 1}
		}
		}, 4);

	this->Add(Wing, 60, 2000000000, {				// Wing of Halloween Dark [C]
		{}
		}, 0);
	this->Add(Wing, 61, 2000000000, {				// Wing of Christmas Angel [C]
		{}
		}, 0);
	//--------------------------------------------------
	// Brilho - Glow
	//--------------------------------------------------
	// Para adicionar brilho a um item, basta:
	// this->Glow.Add(ITEM_GET_MODEL(<item_group>, <item_index>), {<red>, <green>, <blue>});

	// Glow Items

	this->Glow.Add(ITEM_GET_MODEL(7, 18), { 0.79, 0.2844, 0.6467 });		// Set Grand Soul
	this->Glow.Add(ITEM_GET_MODEL(8, 18), { 0.79, 0.2844, 0.6467 });		// Set Grand Soul
	this->Glow.Add(ITEM_GET_MODEL(9, 18), { 0.79, 0.2844, 0.6467 });		// Set Grand Soul
	this->Glow.Add(ITEM_GET_MODEL(10, 18), { 0.79, 0.2844, 0.6467 });		// Set Grand Soul
	this->Glow.Add(ITEM_GET_MODEL(11, 18), { 0.79, 0.2844, 0.6467 });		// Set Grand Soul

	this->Glow.Add(ITEM_GET_MODEL(7, 50), { 0.43, 0.62, 0.427 });			// Set Ashcrow
	this->Glow.Add(ITEM_GET_MODEL(8, 50), { 0.43, 0.62, 0.427 });			// Set Ashcrow
	this->Glow.Add(ITEM_GET_MODEL(9, 50), { 0.43, 0.62, 0.427 });			// Set Ashcrow
	this->Glow.Add(ITEM_GET_MODEL(10, 50), { 0.43, 0.62, 0.427 });			// Set Ashcrow
	this->Glow.Add(ITEM_GET_MODEL(11, 50), { 0.43, 0.62, 0.427 });			// Set Ashcrow

	this->Glow.Add(ITEM_GET_MODEL(7, 51), { 0.1517, 0.33,0.37 });			// Set Eclipse
	this->Glow.Add(ITEM_GET_MODEL(8, 51), { 0.1517, 0.33,0.37 });			// Set Eclipse
	this->Glow.Add(ITEM_GET_MODEL(9, 51), { 0.1517, 0.33,0.37 });			// Set Eclipse
	this->Glow.Add(ITEM_GET_MODEL(10, 51), { 0.1517, 0.33,0.37 });			// Set Eclipse
	this->Glow.Add(ITEM_GET_MODEL(11, 51), { 0.1517, 0.33,0.37 });			// Set Eclipse

	this->Glow.Add(ITEM_GET_MODEL(7, 52), { 0.1875, 0.37, 0.0962 });		// Set Iris
	this->Glow.Add(ITEM_GET_MODEL(8, 52), { 0.1875, 0.37, 0.0962 });		// Set Iris
	this->Glow.Add(ITEM_GET_MODEL(9, 52), { 0.1875, 0.37, 0.0962 });		// Set Iris
	this->Glow.Add(ITEM_GET_MODEL(10, 52), { 0.1875, 0.37, 0.0962 });		// Set Iris
	this->Glow.Add(ITEM_GET_MODEL(11, 52), { 0.1875, 0.37, 0.0962 });		// Set Iris

	this->Glow.Add(ITEM_GET_MODEL(8, 53), { 0.37, 0.2812, 0.3685 });		// Set Valiant
	this->Glow.Add(ITEM_GET_MODEL(9, 53), { 0.37, 0.2812, 0.3685 });		// Set Valiant
	this->Glow.Add(ITEM_GET_MODEL(10, 53), { 0.37, 0.2812, 0.3685 });		// Set Valiant
	this->Glow.Add(ITEM_GET_MODEL(11, 53), { 0.37, 0.2812, 0.3685 });		// Set Valiant

	this->Glow.Add(ITEM_GET_MODEL(7, 54), { 0.48, 0.3599, 0.1008 });		// Set Glorious
	this->Glow.Add(ITEM_GET_MODEL(8, 54), { 0.48, 0.3599, 0.1008 });		// Set Glorious
	this->Glow.Add(ITEM_GET_MODEL(9, 54), { 0.48, 0.3599, 0.1008 });		// Set Glorious
	this->Glow.Add(ITEM_GET_MODEL(10, 54), { 0.48, 0.3599, 0.1008 });		// Set Glorious
	this->Glow.Add(ITEM_GET_MODEL(11, 54), { 0.48, 0.3599, 0.1008 });		// Set Glorious

	this->Glow.Add(ITEM_GET_MODEL(7, 55), { 0.1932 , 0.4411 , 0.84 });		// Set Titan
	this->Glow.Add(ITEM_GET_MODEL(8, 55), { 0.1932 , 0.4411 , 0.84 });		// Set Titan
	this->Glow.Add(ITEM_GET_MODEL(9, 55), { 0.1932 , 0.4411 , 0.84 });		// Set Titan
	this->Glow.Add(ITEM_GET_MODEL(10, 55), { 0.1932 , 0.4411 , 0.84 });		// Set Titan
	this->Glow.Add(ITEM_GET_MODEL(11, 55), { 0.1932 , 0.4411 , 0.84 });		// Set Titan

	this->Glow.Add(ITEM_GET_MODEL(7, 56), { 0.76, 0.361, 0.076 });			// Set Brave
	this->Glow.Add(ITEM_GET_MODEL(8, 56), { 0.76, 0.361, 0.076 });			// Set Brave
	this->Glow.Add(ITEM_GET_MODEL(9, 56), { 0.76, 0.361, 0.076 });			// Set Brave
	this->Glow.Add(ITEM_GET_MODEL(10, 56), { 0.76, 0.361, 0.076 });			// Set Brave
	this->Glow.Add(ITEM_GET_MODEL(11, 56), { 0.76, 0.361, 0.076 });			// Set Brave

	this->Glow.Add(ITEM_GET_MODEL(8, 57), { 0.37, 0.2812, 0.3685 });		// Set Phantom
	this->Glow.Add(ITEM_GET_MODEL(9, 57), { 0.37, 0.2812, 0.3685 });		// Set Phantom
	this->Glow.Add(ITEM_GET_MODEL(10, 57), { 0.37, 0.2812, 0.3685 });		// Set Phantom
	this->Glow.Add(ITEM_GET_MODEL(11, 57), { 0.37, 0.2812, 0.3685 });		// Set Phantom

	this->Glow.Add(ITEM_GET_MODEL(8, 58), { 0.6, 0.1839, 0.162 });			// Set Destroy
	this->Glow.Add(ITEM_GET_MODEL(9, 58), { 0.6, 0.1839, 0.162 });			// Set Destroy
	this->Glow.Add(ITEM_GET_MODEL(10, 58), { 0.6, 0.1839, 0.162 });			// Set Destroy
	this->Glow.Add(ITEM_GET_MODEL(11, 58), { 0.6, 0.1839, 0.162 });			// Set Destroy

	this->Glow.Add(ITEM_GET_MODEL(7, 59), { 0.37, 0.2812, 0.3685 });		// Set Seraphim
	this->Glow.Add(ITEM_GET_MODEL(8, 59), { 0.37, 0.2812, 0.3685 });		// Set Seraphim
	this->Glow.Add(ITEM_GET_MODEL(9, 59), { 0.37, 0.2812, 0.3685 });		// Set Seraphim
	this->Glow.Add(ITEM_GET_MODEL(10, 59), { 0.37, 0.2812, 0.3685 });		// Set Seraphim
	this->Glow.Add(ITEM_GET_MODEL(11, 59), { 0.37, 0.2812, 0.3685 });		// Set Seraphim

	this->Glow.Add(ITEM_GET_MODEL(7, 60), { 0.8, 0.3308, 0.248 });			// Set Royal
	this->Glow.Add(ITEM_GET_MODEL(8, 60), { 0.8, 0.3308, 0.248 });			// Set Royal
	this->Glow.Add(ITEM_GET_MODEL(9, 60), { 0.8, 0.3308, 0.248 });			// Set Royal
	this->Glow.Add(ITEM_GET_MODEL(10, 60), { 0.8, 0.3308, 0.248 });			// Set Royal
	this->Glow.Add(ITEM_GET_MODEL(11, 60), { 0.8, 0.3308, 0.248 });			// Set Royal

	this->Glow.Add(ITEM_GET_MODEL(7, 61), { 0.36, 0.2056, 0.1224 });		// Set Hades
	this->Glow.Add(ITEM_GET_MODEL(8, 61), { 0.36, 0.2056, 0.1224 });		// Set Hades
	this->Glow.Add(ITEM_GET_MODEL(9, 61), { 0.36, 0.2056, 0.1224 });		// Set Hades
	this->Glow.Add(ITEM_GET_MODEL(10, 61), { 0.36, 0.2056, 0.1224 });		// Set Hades
	this->Glow.Add(ITEM_GET_MODEL(11, 61), { 0.36, 0.2056, 0.1224 });		// Set Hades

	this->Glow.Add(ITEM_GET_MODEL(7, 62), { 0.0855, 0.45, 0.2374 });		// Set Queen
	this->Glow.Add(ITEM_GET_MODEL(8, 62), { 0.0855, 0.45, 0.2374 });		// Set Queen
	this->Glow.Add(ITEM_GET_MODEL(9, 62), { 0.0855, 0.45, 0.2374 });		// Set Queen
	this->Glow.Add(ITEM_GET_MODEL(10, 62), { 0.0855, 0.45, 0.2374 });		// Set Queen
	this->Glow.Add(ITEM_GET_MODEL(11, 62), { 0.0855, 0.45, 0.2374 });		// Set Queen

	this->Glow.Add(ITEM_GET_MODEL(7, 63), { 0.31, 0.2114, 0.0527 });		// Set Hollow
	this->Glow.Add(ITEM_GET_MODEL(8, 63), { 0.31, 0.2114, 0.0527 });		// Set Hollow
	this->Glow.Add(ITEM_GET_MODEL(9, 63), { 0.31, 0.2114, 0.0527 });		// Set Hollow
	this->Glow.Add(ITEM_GET_MODEL(10, 63), { 0.31, 0.2114, 0.0527 });		// Set Hollow
	this->Glow.Add(ITEM_GET_MODEL(11, 63), { 0.31, 0.2114, 0.0527 });		// Set Hollow

	this->Glow.Add(ITEM_GET_MODEL(7, 64), { 0.31, 0.2114, 0.0527 });		// Set Hollow Lady
	this->Glow.Add(ITEM_GET_MODEL(8, 64), { 0.31, 0.2114, 0.0527 });		// Set Hollow Lady
	this->Glow.Add(ITEM_GET_MODEL(9, 64), { 0.31, 0.2114, 0.0527 });		// Set Hollow Lady
	this->Glow.Add(ITEM_GET_MODEL(10, 64), { 0.31, 0.2114, 0.0527 });		// Set Hollow Lady
	this->Glow.Add(ITEM_GET_MODEL(11, 64), { 0.31, 0.2114, 0.0527 });		// Set Hollow Lady

	this->Glow.Add(ITEM_GET_MODEL(7, 65), { 0.0,0.0,0.0 });		// Set Rudolph (Christmas)
	this->Glow.Add(ITEM_GET_MODEL(8, 65), { 0.0,0.0,0.0 });		// Set Rudolph (Christmas)
	this->Glow.Add(ITEM_GET_MODEL(9, 65), { 0.0,0.0,0.0 });		// Set Rudolph (Christmas)
	this->Glow.Add(ITEM_GET_MODEL(10, 65), { 0.0,0.0,0.0 });	// Set Rudolph (Christmas)
	this->Glow.Add(ITEM_GET_MODEL(11, 65), { 0.0,0.0,0.0 });	// Set Rudolph (Christmas)

	this->Glow.Add(ITEM_GET_MODEL(7, 66), { 0.0,0.0,0.0 });		// Set Santa (Christmas)
	this->Glow.Add(ITEM_GET_MODEL(8, 66), { 0.0,0.0,0.0 });		// Set Santa (Christmas)
	this->Glow.Add(ITEM_GET_MODEL(9, 66), { 0.0,0.0,0.0 });		// Set Santa (Christmas)
	this->Glow.Add(ITEM_GET_MODEL(10, 66), { 0.0,0.0,0.0 });	// Set Santa (Christmas)
	this->Glow.Add(ITEM_GET_MODEL(11, 66), { 0.0,0.0,0.0 });	// Set Santa (Christmas)

	this->Glow.Add(ITEM_GET_MODEL(7, 67), { 0.0,0.0,0.0 });		// Set Santa Girl (Christmas)
	this->Glow.Add(ITEM_GET_MODEL(8, 67), { 0.0,0.0,0.0 });		// Set Santa Girl (Christmas)
	this->Glow.Add(ITEM_GET_MODEL(9, 67), { 0.0,0.0,0.0 });		// Set Santa Girl (Christmas)
	this->Glow.Add(ITEM_GET_MODEL(10, 67), { 0.0,0.0,0.0 });	// Set Santa Girl (Christmas)
	this->Glow.Add(ITEM_GET_MODEL(11, 67), { 0.0,0.0,0.0 });	// Set Santa Girl (Christmas)

	this->Glow.Add(ITEM_GET_MODEL(7, 68), { 0.53, 0.0318, 0.0318 });		// Set Awakening Elves
	this->Glow.Add(ITEM_GET_MODEL(8, 68), { 0.53, 0.0318, 0.0318 });		// Set Awakening Elves
	this->Glow.Add(ITEM_GET_MODEL(9, 68), { 0.53, 0.0318, 0.0318 });		// Set Awakening Elves
	this->Glow.Add(ITEM_GET_MODEL(10, 68), { 0.53, 0.0318, 0.0318 });		// Set Awakening Elves
	this->Glow.Add(ITEM_GET_MODEL(11, 68), { 0.53, 0.0318, 0.0318 });		// Set Awakening Elves

	this->Glow.Add(ITEM_GET_MODEL(7, 69), { 0.47, 0.2632, 0.0564 });		// Set Awakening Knight
	this->Glow.Add(ITEM_GET_MODEL(8, 69), { 0.47, 0.2632, 0.0564 });		// Set Awakening Knight
	this->Glow.Add(ITEM_GET_MODEL(9, 69), { 0.47, 0.2632, 0.0564 });		// Set Awakening Knight
	this->Glow.Add(ITEM_GET_MODEL(10, 69), { 0.47, 0.2632, 0.0564 });		// Set Awakening Knight
	this->Glow.Add(ITEM_GET_MODEL(11, 69), { 0.47, 0.2632, 0.0564 });		// Set Awakening Knight

	this->Glow.Add(ITEM_GET_MODEL(7, 70), { 0.47, 0.2632, 0.0564 });		// Set Awakening Magic
	this->Glow.Add(ITEM_GET_MODEL(8, 70), { 0.47, 0.2632, 0.0564 });		// Set Awakening Magic
	this->Glow.Add(ITEM_GET_MODEL(9, 70), { 0.47, 0.2632, 0.0564 });		// Set Awakening Magic
	this->Glow.Add(ITEM_GET_MODEL(10, 70), { 0.47, 0.2632, 0.0564 });		// Set Awakening Magic
	this->Glow.Add(ITEM_GET_MODEL(11, 70), { 0.47, 0.2632, 0.0564 });		// Set Awakening Magic

	this->Glow.Add(ITEM_GET_MODEL(7, 71), { 0.1932 , 0.4411 , 0.84 });		// Set Frost Soul Elf
	this->Glow.Add(ITEM_GET_MODEL(8, 71), { 0.1932 , 0.4411 , 0.84 });		// Set Frost Soul Elf
	this->Glow.Add(ITEM_GET_MODEL(9, 71), { 0.1932 , 0.4411 , 0.84 });		// Set Frost Soul Elf
	this->Glow.Add(ITEM_GET_MODEL(10, 71), { 0.1932 , 0.4411 , 0.84 });		// Set Frost Soul Elf
	this->Glow.Add(ITEM_GET_MODEL(11, 71), { 0.1932 , 0.4411 , 0.84 });		// Set Frost Soul Elf

	this->Glow.Add(ITEM_GET_MODEL(7, 72), { 0.1932 , 0.4411 , 0.84 });		// Set Frost Soul Knight
	this->Glow.Add(ITEM_GET_MODEL(8, 72), { 0.1932 , 0.4411 , 0.84 });		// Set Frost Soul Knight
	this->Glow.Add(ITEM_GET_MODEL(9, 72), { 0.1932 , 0.4411 , 0.84 });		// Set Frost Soul Knight
	this->Glow.Add(ITEM_GET_MODEL(10, 72), { 0.1932 , 0.4411 , 0.84 });		// Set Frost Soul Knight
	this->Glow.Add(ITEM_GET_MODEL(11, 72), { 0.1932 , 0.4411 , 0.84 });		// Set Frost Soul Knight

	this->Glow.Add(ITEM_GET_MODEL(7, 73), { 0.1932 , 0.4411 , 0.84 });		// Set Frost Soul Wizard
	this->Glow.Add(ITEM_GET_MODEL(8, 73), { 0.1932 , 0.4411 , 0.84 });		// Set Frost Soul Wizard
	this->Glow.Add(ITEM_GET_MODEL(9, 73), { 0.1932 , 0.4411 , 0.84 });		// Set Frost Soul Wizard
	this->Glow.Add(ITEM_GET_MODEL(10, 73), { 0.1932 , 0.4411 , 0.84 });		// Set Frost Soul Wizard
	this->Glow.Add(ITEM_GET_MODEL(11, 73), { 0.1932 , 0.4411 , 0.84 });		// Set Frost Soul Wizard

	// Glow Armas
	this->Glow.Add(ITEM_GET_MODEL(4, 50), { 1, 0.766, 0.22 });				// HolyAngel Bow
	this->Glow.Add(ITEM_GET_MODEL(4, 51), { 0.98, 0.3548, 0.1274 });		// Awakening Soul Bow

	this->Glow.Add(ITEM_GET_MODEL(0, 50), { 0.1104, 0.46, 0.291 });			// HolyAngel Magic Blade
	this->Glow.Add(ITEM_GET_MODEL(0, 51), { 0.46, 0.1104, 0.2735 });		// HolyAngel Sword
	this->Glow.Add(ITEM_GET_MODEL(0, 52), { 0.98, 0.3548, 0.1274 });		// Awakening Soul Magic Sword
	this->Glow.Add(ITEM_GET_MODEL(0, 53), { 0.98, 0.3548, 0.1274 });		// Awakening Soul Sword

	this->Glow.Add(ITEM_GET_MODEL(5, 50), { 0.1525, 0.4651, 0.61 });		// HolyAngel Staff
	this->Glow.Add(ITEM_GET_MODEL(5, 51), { 0.98, 0.3548, 0.1274 });		// Awakening Soul Staff
	this->Glow.Add(ITEM_GET_MODEL(5, 52), { 0.98, 0.3548, 0.1274 });		// Guardian Staff

	this->Glow.Add(ITEM_GET_MODEL(2, 51), { 0.1525, 0.4651, 0.61 });		// HolyAngel Scepter
	this->Glow.Add(ITEM_GET_MODEL(2, 52), { 0.98, 0.3548, 0.1274 });		// Awakening Soul Scepter

	this->Glow.Add(ITEM_GET_MODEL(0, 55), { 0, 0, 0 });						// Halloween Sword
	this->Glow.Add(ITEM_GET_MODEL(4, 54), { 0, 0, 0 });						// Halloween Bow
	this->Glow.Add(ITEM_GET_MODEL(5, 53), { 0.98, 0.3548, 0.1274 });		// Staff Hollow
	this->Glow.Add(ITEM_GET_MODEL(6, 51), { 0, 0, 0 });						// Halloween Shield

	this->Glow.Add(ITEM_GET_MODEL(0, 56), { 0, 0, 0 });						// Christmas Sword
	this->Glow.Add(ITEM_GET_MODEL(2, 54), { 0, 0, 0 });						// Christmas Mace
	this->Glow.Add(ITEM_GET_MODEL(4, 55), { 0, 0, 0 });						// Christmas Bow
	this->Glow.Add(ITEM_GET_MODEL(5, 54), { 0, 0, 0 });						// Staff Christmas
	this->Glow.Add(ITEM_GET_MODEL(6, 52), { 0, 0, 0 });						// Christmas Shield

	this->Glow.Add(ITEM_GET_MODEL(0, 54), { 0.0648, 0.2665, 0.36 });		// Guardian Sword
	this->Glow.Add(ITEM_GET_MODEL(1, 50), { 0.0648, 0.2665, 0.36 });		// Guardian Axe
	this->Glow.Add(ITEM_GET_MODEL(2, 53), { 0.0648, 0.2665, 0.36 });		// Guardian Mace
	this->Glow.Add(ITEM_GET_MODEL(4, 52), { 0.0648, 0.2665, 0.36 });		// Guardian Bow
	this->Glow.Add(ITEM_GET_MODEL(4, 53), { 0.0648, 0.2665, 0.36 });		// Guardian CrossBow
	this->Glow.Add(ITEM_GET_MODEL(5, 52), { 0.0648, 0.2665, 0.36 });		// Guardian Staff
	this->Glow.Add(ITEM_GET_MODEL(6, 50), { 0.0648, 0.2665, 0.36 });		// Guardian Shield

	this->Glow.Add(ITEM_GET_MODEL(6, 52), { 0, 0, 0 });						// Christmas Shield

	//Items 2020 (Armas)
	this->Glow.Add(ITEM_GET_MODEL(6, 53), { 0, 0, 0 });										// Shield Of Demonic
	this->Glow.Add(ITEM_GET_MODEL(6, 54), { 0.1035, 0.3056, 0.45 });						// Shield Of Angel
	this->Glow.Add(ITEM_GET_MODEL(6, 55), { 0, 0, 0 });										// Shield Of Slayer
	this->Glow.Add(ITEM_GET_MODEL(6, 56), { 0.29, 0.0667, 0.1188 });						// Shield Of King
	this->Glow.Add(ITEM_GET_MODEL(6, 57), { 0.45, 0.3967, 0.0945 });						// Shield Of Vikings

	this->Glow.Add(ITEM_GET_MODEL(5, 55), { 0.0648, 0.2665, 0.36 });						// Staff Of Angel
	this->Glow.Add(ITEM_GET_MODEL(5, 56), { 0.0648, 0.2665, 0.36 });						// Staff Of Death
	this->Glow.Add(ITEM_GET_MODEL(5, 57), { 0.0648, 0.2665, 0.36 });						// Staff Of Demonic

	this->Glow.Add(ITEM_GET_MODEL(2, 55), { 0, 0, 0 });										// Scepter Of Dryad
	this->Glow.Add(ITEM_GET_MODEL(2, 56), { 0, 0, 0 });										// Scepter Of King

	this->Glow.Add(ITEM_GET_MODEL(0, 57), { 0.38, 0.2711, 0.0532 });						// Sword Of Titan
	this->Glow.Add(ITEM_GET_MODEL(0, 58), { 0.3, 0.045, 0.045 });							// Sword Of King
	this->Glow.Add(ITEM_GET_MODEL(0, 59), { 0.0667, 0.2863, 0.29 });						// Sword Of Slayer
	this->Glow.Add(ITEM_GET_MODEL(0, 60), { 0.2532, 0.38, 0.0874 });						// Sword Of Vikings
	//====================

	this->Glow.Add(ITEM_GET_MODEL(14, 50), { 0, 0, 0 });			// Box of Yelow
	this->Glow.Add(ITEM_GET_MODEL(14, 51), { 0, 0, 0 });			// Box of Red
	this->Glow.Add(ITEM_GET_MODEL(14, 52), { 0, 0, 0 });			// Box of Green
	this->Glow.Add(ITEM_GET_MODEL(14, 53), { 0, 0, 0 });			// Box of Blue
	this->Glow.Add(ITEM_GET_MODEL(14, 54), { 0, 0, 0 });			// Box of Pink
	this->Glow.Add(ITEM_GET_MODEL(14, 55), { 0, 0, 0 });			// Box of Halloween

	this->Glow.Add(ITEM_GET_MODEL(14, 56), { 0, 0, 0 });			// Cofre de Bronce
	this->Glow.Add(ITEM_GET_MODEL(14, 57), { 0, 0, 0 });			// Cofre de Plata
	this->Glow.Add(ITEM_GET_MODEL(14, 58), { 0, 0, 0 });			// Cofre de Oro

	this->Glow.Add(ITEM_GET_MODEL(14, 59), { 0, 0, 0 });				// Invitation to Santa Village
	this->Glow.Add(ITEM_GET_MODEL(14, 60), { 0.79, 0.2607, 0.2607 });	// Box of Christmas

	this->Glow.Add(ITEM_GET_MODEL(14, 61), { 0, 0, 0 });				// Box of VIP
	this->Glow.Add(ITEM_GET_MODEL(14, 62), { 0, 0, 0 });				// Box of Wing

	this->Glow.Add(ITEM_GET_MODEL(14, 160), { 0, 0, 0 });			// Lucky Clover
	this->Glow.Add(ITEM_GET_MODEL(14, 161), { 0, 0, 0 });			// Jewel of Blow
	this->Glow.Add(ITEM_GET_MODEL(14, 162), { 0, 0, 0 });			// Jewel of Power
	this->Glow.Add(ITEM_GET_MODEL(14, 163), { 0, 0, 0 });			// Jewel of Ruin
	this->Glow.Add(ITEM_GET_MODEL(14, 164), { 0, 0, 0 });			// Crystal of Change
	this->Glow.Add(ITEM_GET_MODEL(14, 165), { 0, 0, 0 });			// Jewel of Special
	this->Glow.Add(ITEM_GET_MODEL(14, 166), { 0, 0, 0 });			// Jewel of Ancient 1
	this->Glow.Add(ITEM_GET_MODEL(14, 167), { 0, 0, 0 });			// Jewel of Ancient 2

	//--------------------------------------------------
	// Descrições - Descriptions
	//--------------------------------------------------
	// Para adicionar descrições a um item, basta:
	// this->Description.Add(ITEM_GET(<item_group>, <item_index>), "<text>", {<bg_red>, <bg_green>, <bg_blue>, <bg_alpha>}, {<fg_red>, <fg_green>, <fg_blue>, <fg_alpha>}, <bold?>);
	// bg_* -> Cor do fundo (background)
	// fg_* -> Cor do texto (foreground)
	// bold? -> Ativar negrito? 1: sim - 0: não

	this->Description.Add(ITEM_GET(14, 160), "Esta joya puede agregar Luck a armas y armaduras.", { 94,150,37,160 }, { 255,255,255,230 }, 0);
	this->Description.Add(ITEM_GET(14, 160), "El % de éxito es de 40% para FREE y 45% para VIP", { 198,140,30,180 }, { 255,255,255,250 }, 0);

	this->Description.Add(ITEM_GET(14, 161), "Esta joya puede agregar skill a cualquier arma.", { 94,150,37,160 }, { 255,255,255,230 }, 0);
	this->Description.Add(ITEM_GET(14, 161), "El % de éxito es de 40% para FREE y 45% para VIP", { 198,140,30,180 }, { 255,255,255,250 }, 0);

	this->Description.Add(ITEM_GET(14, 162), "Esta joya puede agregar una opcion excellent a cualquier item.", { 94,150,37,160 }, { 255,255,255,230 }, 0);
	this->Description.Add(ITEM_GET(14, 162), "El % de éxito es de 40% para FREE y 45% para VIP", { 198,140,30,180 }, { 255,255,255,250 }, 0);

	this->Description.Add(ITEM_GET(14, 163), "Esta joya puede hacer FULL cualquier item.", { 94,150,37,160 }, { 255,255,255,230 }, 0);
	this->Description.Add(ITEM_GET(14, 163), "Tenga cuidado, puede romper su item.", { 186,27,27,180 }, { 255,255,255,230 }, 0);
	this->Description.Add(ITEM_GET(14, 163), "El % de éxito es de 1% para FREE y 2% para VIP", { 198,140,30,180 }, { 255,255,255,250 }, 0);

	this->Description.Add(ITEM_GET(14, 164), "Esta joya puede subir a +13 a cualquier item +9.", { 94,150,37,160 }, { 255,255,255,230 }, 0);
	this->Description.Add(ITEM_GET(14, 164), "Tenga cuidado, puede volver su item a +0.", { 186,27,27,180 }, { 255,255,255,230 }, 0);
	this->Description.Add(ITEM_GET(14, 164), "El % de éxito es de 5% para FREE y 7% para VIP", { 198,140,30,180 }, { 255,255,255,250 }, 0);

	this->Description.Add(ITEM_GET(14, 165), "Special Jewel", { 198,140,30,180 }, { 255,255,255,250 }, 0);

	this->Description.Add(ITEM_GET(14, 166), "Esta joya hace ancient un item!", { 198,140,30,0 }, { 244,221,33,250 }, 1);
	this->Description.Add(ITEM_GET(14, 166), "No funciona con items con Opciones!", { 186,27,27,180 }, { 255,255,255,230 }, 0);

	this->Description.Add(ITEM_GET(14, 167), "Esta joya hace ancient un item!", { 198,140,30,0 }, { 244,221,33,250 }, 1);
	this->Description.Add(ITEM_GET(14, 167), "No funciona con items con Opciones!", { 186,27,27,180 }, { 255,255,255,230 }, 0);

	this->Description.Add(ITEM_GET(14, 50), "Esta box dropea las partes faltantes de los sets!", { 235,212,30,110 }, { 255,255,255,250 }, 0);
	this->Description.Add(ITEM_GET(14, 51), "Esta box dropea las partes faltantes de los sets!", { 235,30,30,150 }, { 255,255,255,250 }, 0);
	this->Description.Add(ITEM_GET(14, 52), "Esta box dropea los sets nuevos !", { 105,198,30,150 }, { 255,255,255,250 }, 0);
	this->Description.Add(ITEM_GET(14, 53), "Esta box dropea las partes faltantes de los sets!", { 30,134,235,150 }, { 255,255,255,250 }, 0);
	this->Description.Add(ITEM_GET(14, 54), "Esta box dropea las partes faltantes de los sets!", { 189,30,235,150 }, { 255,255,255,250 }, 0);

	this->Description.Add(ITEM_GET(14, 55), "Esta box dropea items especiales halloween!", { 198,140,30,180 }, { 255,255,255,250 }, 0);
	this->Description.Add(ITEM_GET(14, 60), "Esta box dropea items especiales navideños!", { 201,66,66,180 }, { 255,255,255,250 }, 0);

	this->Description.Add(ITEM_GET(7, 63), "SET ESPECIAL HALLOWEEN", { 198,140,30,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(8, 63), "SET ESPECIAL HALLOWEEN", { 198,140,30,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(9, 63), "SET ESPECIAL HALLOWEEN", { 198,140,30,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(10, 63), "SET ESPECIAL HALLOWEEN", { 198,140,30,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(11, 63), "SET ESPECIAL HALLOWEEN", { 198,140,30,180 }, { 255,255,255,250 }, 1);

	this->Description.Add(ITEM_GET(7, 64), "SET ESPECIAL HALLOWEEN", { 198,140,30,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(8, 64), "SET ESPECIAL HALLOWEEN", { 198,140,30,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(9, 64), "SET ESPECIAL HALLOWEEN", { 198,140,30,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(10, 64), "SET ESPECIAL HALLOWEEN", { 198,140,30,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(11, 64), "SET ESPECIAL HALLOWEEN", { 198,140,30,180 }, { 255,255,255,250 }, 1);

	this->Description.Add(ITEM_GET(7, 65), "SET ESPECIAL DE NAVIDAD", { 201,66,66,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(8, 65), "SET ESPECIAL DE NAVIDAD", { 201,66,66,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(9, 65), "SET ESPECIAL DE NAVIDAD", { 201,66,66,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(10, 65), "SET ESPECIAL DE NAVIDAD", { 201,66,66,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(11, 65), "SET ESPECIAL DE NAVIDAD", { 201,66,66,180 }, { 255,255,255,250 }, 1);

	this->Description.Add(ITEM_GET(7, 66), "SET ESPECIAL DE NAVIDAD", { 201,66,66,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(8, 66), "SET ESPECIAL DE NAVIDAD", { 201,66,66,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(9, 66), "SET ESPECIAL DE NAVIDAD", { 201,66,66,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(10, 66), "SET ESPECIAL DE NAVIDAD", { 201,66,66,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(11, 66), "SET ESPECIAL DE NAVIDAD", { 201,66,66,180 }, { 255,255,255,250 }, 1);

	this->Description.Add(ITEM_GET(7, 67), "SET ESPECIAL DE NAVIDAD", { 201,66,66,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(8, 67), "SET ESPECIAL DE NAVIDAD", { 201,66,66,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(9, 67), "SET ESPECIAL DE NAVIDAD", { 201,66,66,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(10, 67), "SET ESPECIAL DE NAVIDAD", { 201,66,66,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(11, 67), "SET ESPECIAL DE NAVIDAD", { 201,66,66,180 }, { 255,255,255,250 }, 1);

	this->Description.Add(ITEM_GET(0, 55), "ITEM ESPECIAL HALLOWEEN", { 198,140,30,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(4, 54), "ITEM ESPECIAL HALLOWEEN", { 198,140,30,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(5, 53), "ITEM ESPECIAL HALLOWEEN", { 198,140,30,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(6, 51), "ITEM ESPECIAL HALLOWEEN", { 198,140,30,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(12, 60), "ITEM ESPECIAL HALLOWEEN", { 198,140,30,180 }, { 255,255,255,250 }, 1);

	this->Description.Add(ITEM_GET(0, 56), "ITEM ESPECIAL DE NAVIDAD", { 201,66,66,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(2, 54), "ITEM ESPECIAL DE NAVIDAD", { 201,66,66,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(4, 55), "ITEM ESPECIAL DE NAVIDAD", { 201,66,66,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(5, 54), "ITEM ESPECIAL DE NAVIDAD", { 201,66,66,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(6, 52), "ITEM ESPECIAL DE NAVIDAD", { 201,66,66,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(12, 61), "ITEM ESPECIAL DE NAVIDAD", { 201,66,66,180 }, { 255,255,255,250 }, 1);

	this->Description.Add(ITEM_GET(14, 56), "Cofre de bronce 500.000.000 zen", { 198,140,30,0 }, { 210,152,26,250 }, 1);
	//this->Description.Add(ITEM_GET(14, 56), "Al vender fijarse de tener espacio para el zen!", { 186,27,27,180 }, { 255,255,255,230 }, 0);
	this->Description.Add(ITEM_GET(14, 57), "Cofre de plata 1.000.000.000 zen", { 198,140,30,0 }, { 209,209,205,250 }, 1);
	//this->Description.Add(ITEM_GET(14, 57), "Al vender fijarse de tener espacio para el zen!", { 186,27,27,180 }, { 255,255,255,230 }, 0);
	this->Description.Add(ITEM_GET(14, 58), "Cofre de Oro 1.500.000.000 zen", { 198,140,30,0 }, { 244,221,33,250 }, 1);
	//this->Description.Add(ITEM_GET(14, 58), "Al vender fijarse de tener espacio para el zen!", { 186,27,27,180 }, { 255,255,255,230 }, 0);

	this->Description.Add(ITEM_GET(14, 59), "Entrega la entrada al 'NPC Snowman' en Devias", { 198,140,30,0 }, { 244,221,33,250 }, 1);

	this->Description.Add(ITEM_GET(14, 61), "Esta caja solo se obtiene con Coins", { 198,140,30,0 }, { 244,221,33,250 }, 1);
	this->Description.Add(ITEM_GET(14, 61), "Dropea items que no encontraras", { 198,140,30,0 }, { 209,209,205,250 }, 1);
	this->Description.Add(ITEM_GET(14, 61), "En ningun otro sitio.", { 198,140,30,0 }, { 209,209,205,250 }, 1);
	this->Description.Add(ITEM_GET(14, 61), "Dropea items nuevos +10/+13", { 198,140,30,0 }, { 124,179,66,250 }, 1);

	this->Description.Add(ITEM_GET(14, 62), "Esta caja solo se obtiene con Coins", { 198,140,30,0 }, { 244,221,33,250 }, 1);
	this->Description.Add(ITEM_GET(14, 62), "Dropea alas FULL OPT !", { 198,140,30,0 }, { 124,179,66,250 }, 1);

	this->Description.Add(ITEM_GET(6, 53), "SHIELD TEMPORADA 2020", { 201,66,66,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(6, 54), "SHIELD TEMPORADA 2020", { 201,66,66,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(6, 55), "SHIELD TEMPORADA 2020", { 201,66,66,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(6, 56), "SHIELD TEMPORADA 2020", { 201,66,66,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(6, 57), "SHIELD TEMPORADA 2020", { 201,66,66,180 }, { 255,255,255,250 }, 1);

	this->Description.Add(ITEM_GET(5, 55), "STAFF TEMPORADA 2020", { 201,66,66,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(5, 56), "STAFF TEMPORADA 2020", { 201,66,66,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(5, 57), "STAFF TEMPORADA 2020", { 201,66,66,180 }, { 255,255,255,250 }, 1);

	this->Description.Add(ITEM_GET(2, 55), "SCEPTER TEMPORADA 2020", { 201,66,66,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(2, 56), "SCEPTER TEMPORADA 2020", { 201,66,66,180 }, { 255,255,255,250 }, 1);

	this->Description.Add(ITEM_GET(0, 57), "SWORD TEMPORADA 2020", { 201,66,66,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(0, 58), "SWORD TEMPORADA 2020", { 201,66,66,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(0, 59), "SWORD TEMPORADA 2020", { 201,66,66,180 }, { 255,255,255,250 }, 1);
	this->Description.Add(ITEM_GET(0, 60), "SWORD TEMPORADA 2020", { 201,66,66,180 }, { 255,255,255,250 }, 1);

	this->Hook();
}

void Item::Hook()
{
	Memory::Hook<false>(0x5069A2, this->SetGlow);
	Memory::Hook<false>(0x5F8445, this->SetGlow);
	Memory::Hook<false>(0x491F31, this->MakePreviewCharacter);
	Memory::Hook<false>(0x4BC6D7, this->MakePreviewCharacter);
	Memory::Hook<false>(0x4C1F87, this->MakePreviewCharacter);
	Memory::Hook<false>(0x4C2D98, this->MakePreviewCharacter);
	Memory::Hook<false>(0x4DA13F, this->MakePreviewCharacter);
	Memory::Hook<false>(0x4DBE44, this->MakePreviewCharacter);
	Memory::Hook<true>(0x5A7420, this->SetDescriptionInfo);
	Memory::Hook<true>(0x59E78D, this->SetDescriptionColor1);
	Memory::Hook<true>(0x59EBE7, this->SetDescriptionColor2);
	Memory::Hook<true>(0x540A98, this->NewWings1);
	Memory::Hook<true>(0x540EC6, this->NewWings2);
	Memory::Hook<true>(0x540FA3, this->NewWings3);
	Memory::Hook<true>(0x541252, this->NewWings4);
	Memory::Hook<true>(0x5414B8, this->NewWings5);
	Memory::Hook<true>(0x541703, this->NewWings6);
	Memory::Hook<true>(0x54222B, this->NewWings7);
	Memory::Hook<true>(0x542292, this->NewWings8);
	Memory::Hook<true>(0x54236B, this->NewWings9);
	Memory::Hook<true>(0x542AF5, this->NewWings10);
	Memory::Hook<true>(0x542B4F, this->NewWings11);
	Memory::Hook<true>(0x542C00, this->NewWings12);
	Memory::Hook<true>(0x542D95, this->NewWings13);
	Memory::Hook<true>(0x58A06B, this->NewWings14);
	Memory::Hook<true>(0x5A1381, this->NewWings15);
	Memory::Hook<true>(0x5A1917, this->NewWings16);
	Memory::Hook<true>(0x5A2382, this->NewWings17);
	Memory::Hook<true>(0x5A3945, this->NewWings18);
	Memory::Hook<true>(0x5A5317, this->NewWings19);
	Memory::Hook<true>(0x5A5FF8, this->NewWings20);
	Memory::Hook<true>(0x5A7708, this->NewWings21);
	Memory::Hook<true>(0x5A7D77, this->NewWings22);
	Memory::Hook<true>(0x5AB4AA, this->NewWings23);
	Memory::Hook<true>(0x5B1843, this->NewWings24);
	Memory::Hook<true>(0x5B1880, this->NewWings25);
	Memory::Hook<true>(0x5C6D27, this->NewWings26);
	Memory::Hook<true>(0x5CD77D, this->NewWings27);
	Memory::Hook<true>(0x5CDE8A, this->NewWings28);
	//Memory::Hook<true>(0x5EBB71, this->NewWings29); -> chaos_machine
	Memory::Hook<true>(0x5EBDFC, this->NewWings30);
	Memory::Hook<true>(0x5D0434, this->NewWings31);
	Memory::Hook<true>(0x5AA341, this->NewWings32);
	Memory::Hook<true>(0x5F9DE1, this->NewWings33);
	Memory::Hook<true>(0x5F874E, this->NewWings34);
	Memory::Hook<true>(0x540FC7, this->NewWings35);
	Memory::Hook<true>(0x540FE7, this->NewWings36);
	Memory::Hook<true>(0x541AA2, this->NewWings37);
	Memory::Hook<true>(0x5B8E66, this->NewJewels1);
	Memory::Hook<true>(0x541D9F, this->NewJewels2);
	Memory::Hook<true>(0x5F88A2, this->NewJewels3);
	Memory::Hook<true>(0x5C6CEB, this->NewJewels4);
	Memory::Hook<true>(0x5CF247, this->NewBows1);
	Memory::Hook<true>(0x4EB652, this->NewBows2);
	Memory::Hook<true>(0x4EA96C, this->NewBows3);
	Memory::Hook<true>(0x5048F3, this->NewBows4);
	Memory::Hook<true>(0x4EC5CA, this->NewBows5);
	Memory::Hook<true>(0x4EC837, this->NewBows6);
	Memory::Hook<true>(0x555F62, this->NewBows7);
	Memory::Hook<true>(0x54C3F0, this->NewBows8);
	Memory::Hook<true>(0x543AE8, this->NewBows9);
	Memory::Hook<true>(0x5A811A, this->NewBows10);
	Memory::Hook<true>(0x55930B, this->NewBows11);
	Memory::Hook<true>(0x58D58F, this->NewBows12);
	Memory::Hook<true>(0x555BF5, this->NewBows13);
	Memory::Hook<true>(0x54C052, this->NewBows14);
	Memory::Hook<true>(0x572594, this->NewBows15);
	Memory::Hook<true>(0x570D2B, this->NewBows16);
	Memory::Hook<true>(0x4EC5E9, this->NewCrossbows1);
	Memory::Hook<true>(0x4EC861, this->NewCrossbows2);
	Memory::Hook<true>(0x53382A, this->NewCrossbows3);
	Memory::Hook<true>(0x4EB671, this->NewCrossbows4);
	Memory::Hook<true>(0x4C58D4, this->NewCrossbows5);
	Memory::Hook<true>(0x5F54C0, this->NewCrossbows6);
	Memory::Hook<true>(0x50491D, this->NewCrossbows7);
	Memory::Hook<true>(0x5001A1, this->NewCrossbows8);
	Memory::Hook<true>(0x4EA98B, this->NewCrossbows9);
	Memory::Hook<true>(0x53347F, this->MultipleShotSkillEffect);
	Memory::Hook<true>(0x53362F, this->SingleShotSkillEffect);
	Memory::Hook<true>(0x500765, this->WingEffect);
	Memory::Hook<true>(0x5F99A8, this->GlowEffect);

	// Item description limit (desbugar itens ancients)
	memset(ItemDescription, 0, sizeof(ItemDescription));
	memset(ItemDescriptionColor, 0, sizeof(ItemDescriptionColor));
	memset(ItemDescriptionType, 0, sizeof(ItemDescriptionType));

	Memory::Update<DWORD>(0x40C254, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x40C2A4, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x40CD4F, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x40CE23, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x40CE69, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x40CEAD, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x40CEF3, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x40CF3B, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x40CF81, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x40CFDC, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x40D18A, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x40D1CD, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x40D334, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x40D350, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x40D36B, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x40D4DA, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x40D500, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x40D527, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x40D543, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x40D570, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x40D729, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x40D745, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x4200F9, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x420182, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x420F2C, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x42101A, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x4214A3, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x421525, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x421571, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x4215A1, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x4215BD, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x4215F6, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x421621, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x421668, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x42168E, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x4216B7, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x4216F0, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x421967, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x421B18, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x421CFF, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x421F29, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x421F55, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x421F82, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x42201A, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x422045, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x42208B, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x432D39, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x432D5C, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x432D98, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x43310A, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x43313E, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x4331B8, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x4331D4, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x433211, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x433230, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x492555, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x49258E, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x4925C2, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5960A2, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x59625F, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x59635E, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x599689, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5996C2, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5996F6, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x59E661, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x59E6FB, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x59E8C8, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x59EB17, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x59EE27, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x59EE82, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x59EEBB, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x59EF11, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x59EFA4, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x59F04A, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x59F10D, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x59F20C, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x59F385, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x59FD77, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x59FDA6, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x59FDE7, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x59FE0F, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x59FE76, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x59FEC0, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x59FEF3, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x59FF34, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x59FF5C, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x59FFC3, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A01B9, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A01E3, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A0228, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A0260, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A0286, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A02AC, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A0417, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A043D, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A050A, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A0580, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A05BC, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A21E8, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A222A, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A252D, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A2620, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A27D0, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A2855, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A2D4C, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A2D72, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A2DC2, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A2DE8, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A2E5D, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A2E81, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A2EC0, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A2EEF, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A2F46, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A2F76, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A2FC2, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A2FE2, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A300C, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A302C, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A3069, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A3089, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A3157, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A31AD, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A31CD, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A31F1, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A323D, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A325D, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A32A1, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A32CB, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A32EB, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A332D, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A3365, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A33A7, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A33C7, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A36DB, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A39F2, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A3B17, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A3B53, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A3B8A, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A3BBE, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A3BF0, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A3C2D, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A3C75, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A3CAD, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A3CDA, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A3D34, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A3D85, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A3DD3, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A3E22, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A3E57, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A3E8C, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A3EC0, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A3EFA, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A3F35, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A3F9D, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A3FD1, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A4007, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A4060, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A4094, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A40CA, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A4105, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A413E, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A4174, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A41AD, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A41E3, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A4217, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A424B, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A429E, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A42D2, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A430B, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A433F, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A437B, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A43C4, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A43F8, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A4431, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A4465, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A4493, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A44C7, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A4500, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A4534, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A455D, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A459C, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A45D0, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A463B, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A4B40, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A4BF0, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A4C5B, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A4C9F, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A4CF5, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A4D37, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A4D7E, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A4DB2, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A4DF2, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A4E26, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A4E3B, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A4E6F, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A4EAC, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A4F26, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A4F5A, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A4F9F, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A4FD3, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A5015, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A5050, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A508B, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A50D0, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A510B, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A5146, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A5181, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A51BE, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A51F4, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A522F, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A5281, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A52B6, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A52EA, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A5331, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A5378, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A53AE, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A53E2, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A5407, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A544C, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A5477, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A54C9, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A54F9, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A5518, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A5537, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A557E, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A55AE, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A55CD, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A55EC, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A561D, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A5670, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A56C0, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A56E6, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A5719, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A574D, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A579D, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A57D6, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A580A, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A583E, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A5877, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A58CC, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A58F1, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A5906, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A5E28, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A5E7F, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A5F0D, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A5F40, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A5F8B, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A60F8, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A613A, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A6160, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A6185, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A61DB, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A6210, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A625C, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A62C4, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A65C7, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A6802, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A6B05, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A6CD6, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A6D45, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A6DC8, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A6E34, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A6EA0, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A6F0C, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A6F78, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A6FE4, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A7075, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A70A8, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A70F8, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A712B, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A7187, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A71C0, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A720A, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A7243, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A7283, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A730A, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A7350, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A736D, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A7387, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A73DE, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A742E, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A7472, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A7661, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A774B, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A77CE, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A77F7, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A7836, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A7B29, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A7DD2, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A7DF7, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A7E19, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A7E54, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A7EB3, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A7EED, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A7F1A, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A877E, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A89EC, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A8A1A, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A8A4E, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A8A82, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A8AB4, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A8B04, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A8B66, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A8BC7, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A8EF9, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A8F39, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A90D6, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A9117, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A9375, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A93A7, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x5A95D1, (DWORD)(&ItemDescription));
	Memory::Update<DWORD>(0x40CD8A, (DWORD)(&ItemDescription[1]));
	Memory::Update<DWORD>(0x40D1F2, (DWORD)(&ItemDescription[1]));
	Memory::Update<DWORD>(0x420115, (DWORD)(&ItemDescription[1]));
	Memory::Update<DWORD>(0x420F53, (DWORD)(&ItemDescription[1]));
	Memory::Update<DWORD>(0x42106E, (DWORD)(&ItemDescription[1]));
	Memory::Update<DWORD>(0x4214C1, (DWORD)(&ItemDescription[1]));
	Memory::Update<DWORD>(0x5960BB, (DWORD)(&ItemDescription[1]));
	Memory::Update<DWORD>(0x5A8797, (DWORD)(&ItemDescription[1]));
	Memory::Update<DWORD>(0x40CDA8, (DWORD)(&ItemDescription[2]));
	Memory::Update<DWORD>(0x40D20E, (DWORD)(&ItemDescription[2]));
	Memory::Update<DWORD>(0x420127, (DWORD)(&ItemDescription[2]));
	Memory::Update<DWORD>(0x42143B, (DWORD)(&ItemDescription[2]));
	Memory::Update<DWORD>(0x5960D9, (DWORD)(&ItemDescription[2]));
	Memory::Update<DWORD>(0x5A87B8, (DWORD)(&ItemDescription[2]));
	Memory::Update<DWORD>(0x40D220, (DWORD)(&ItemDescription[3]));
	Memory::Update<DWORD>(0x420160, (DWORD)(&ItemDescription[3]));
	Memory::Update<DWORD>(0x42145D, (DWORD)(&ItemDescription[3]));
	Memory::Update<DWORD>(0x59610D, (DWORD)(&ItemDescription[3]));
	Memory::Update<DWORD>(0x5961CF, (DWORD)(&ItemDescription[3]));
	Memory::Update<DWORD>(0x5961DB, (DWORD)(&ItemDescription[3]));
	Memory::Update<DWORD>(0x5961E7, (DWORD)(&ItemDescription[3]));
	Memory::Update<DWORD>(0x5961F3, (DWORD)(&ItemDescription[3]));
	Memory::Update<DWORD>(0x5961FF, (DWORD)(&ItemDescription[3]));
	Memory::Update<DWORD>(0x59620B, (DWORD)(&ItemDescription[3]));
	Memory::Update<DWORD>(0x5A8850, (DWORD)(&ItemDescription[3]));
	Memory::Update<DWORD>(0x5A892D, (DWORD)(&ItemDescription[3]));
	Memory::Update<DWORD>(0x5A895D, (DWORD)(&ItemDescription[3]));
	Memory::Update<DWORD>(0x40D249, (DWORD)(&ItemDescription[4]));
	Memory::Update<DWORD>(0x596222, (DWORD)(&ItemDescription[4]));
	Memory::Update<DWORD>(0x5A8871, (DWORD)(&ItemDescription[4]));
	Memory::Update<DWORD>(0x596234, (DWORD)(&ItemDescription[5]));
	Memory::Update<DWORD>(0x5A88A4, (DWORD)(&ItemDescription[5]));
	Memory::Update<DWORD>(0x40C266, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x40C2B4, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x40CD7A, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x40CE38, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x40CEC2, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x40CF50, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x40CF96, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x40D005, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x40D018, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x40D183, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x40D510, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x40D556, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x4200DC, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x420F3F, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x421030, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x421044, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x42105F, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x4214A9, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x4214DB, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x421593, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x421943, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x421977, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x42198A, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x421CE9, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x421D0F, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x421D18, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x421F47, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x421FBB, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x42202F, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x422052, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x432D6C, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x432DA8, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x433100, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x43311A, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x433174, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x433181, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x4331EA, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x433240, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x49256F, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x4925A3, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x4925DD, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x59624A, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5996A3, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5996D7, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x599711, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x59E70B, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x59EB65, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x59EE9E, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x59EEDA, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x59EF66, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x59EF76, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x59F012, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x59F022, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x59F0A6, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x59F0B6, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x59F0FB, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x59F223, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x59F230, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x59F39E, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x59FDCA, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x59FE43, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x59FF17, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x59FF90, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A023D, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A042F, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A0480, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A04E3, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A0558, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A21C2, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A263D, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A27ED, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A2807, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A2821, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A282E, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A2D34, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A2DA6, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A3C15, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A3C63, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A3C9C, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A3D53, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A3DA4, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A3DF2, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A3E37, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A3E6C, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A3EA1, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A3F14, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A3F4D, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A3FB2, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A3FE6, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A401C, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A4075, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A40A9, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A40DF, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A411F, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A4153, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A4189, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A41C2, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A41F8, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A422C, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A4263, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A42B3, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A42EC, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A4320, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A4354, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A4390, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A43D9, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A4412, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A4446, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A447A, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A44A8, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A44E1, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A4515, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A4549, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A4572, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A45B1, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A45E5, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A4BA6, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A4BBB, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A4C1A, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A4C2C, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A4C70, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A4CBB, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A4CC8, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A4D0A, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A4D4C, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A4D93, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A4DC7, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A4E07, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A4E50, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A4E84, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A4EC1, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A4F3B, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A4F6F, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A4FB4, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A4FE8, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A502A, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A5065, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A50A0, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A50E5, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A5120, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A515B, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A5196, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A51D3, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A5209, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A5244, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A5296, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A52CB, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A52FF, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A534A, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A538D, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A542A, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A54A0, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A5555, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A560C, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A564B, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A565E, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A5692, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A56AE, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A572E, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A5762, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A57B7, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A57EB, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A581F, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A5858, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A588C, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A591B, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A5E0C, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A5E45, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A5EAB, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A5ED4, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A5F58, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A5F77, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A619A, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A61F0, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A6225, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A6271, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A6599, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A65DC, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A65E7, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A6ADE, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A6B1A, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A6B3D, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A6D22, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A6D5A, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A6D7F, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A6E11, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A6E49, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A6E57, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A6EE9, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A6F21, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A6F2F, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A6FC1, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A6FF9, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A7007, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A70C2, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A7145, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A71DA, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A725D, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A7322, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A739C, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A73F3, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A780C, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A7E3C, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A7ECA, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A8A2C, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A8A60, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A8A95, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A8AC4, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A8B14, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A8B76, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A8BD7, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A8F14, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A8F4F, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A90F6, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A9127, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x5A9385, (DWORD)(&ItemDescriptionColor));
	Memory::Update<DWORD>(0x40CD98, (DWORD)(&ItemDescriptionColor[1]));
	Memory::Update<DWORD>(0x40D200, (DWORD)(&ItemDescriptionColor[1]));
	Memory::Update<DWORD>(0x420107, (DWORD)(&ItemDescriptionColor[1]));
	Memory::Update<DWORD>(0x5960C9, (DWORD)(&ItemDescriptionColor[1]));
	Memory::Update<DWORD>(0x5A87A9, (DWORD)(&ItemDescriptionColor[1]));
	Memory::Update<DWORD>(0x40CDB3, (DWORD)(&ItemDescriptionColor[2]));
	Memory::Update<DWORD>(0x421441, (DWORD)(&ItemDescriptionColor[2]));
	Memory::Update<DWORD>(0x59EE03, (DWORD)(&ItemDescriptionColor[2]));
	Memory::Update<DWORD>(0x59EDFC, (DWORD)(&ItemDescriptionColor[3]));
	Memory::Update<DWORD>(0x5A8860, (DWORD)(&ItemDescriptionColor[3]));
	Memory::Update<DWORD>(0x5A893B, (DWORD)(&ItemDescriptionColor[3]));
	Memory::Update<DWORD>(0x5A896C, (DWORD)(&ItemDescriptionColor[3]));
	Memory::Update<DWORD>(0x40D246, (DWORD)(&ItemDescriptionColor[4]));
	Memory::Update<DWORD>(0x5A8888, (DWORD)(&ItemDescriptionColor[4]));
	Memory::Update<DWORD>(0x5A88B2, (DWORD)(&ItemDescriptionColor[5]));
	Memory::Update<DWORD>(0x40CD80, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x40CE42, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x40CECC, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x40CF57, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x40CFA1, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x40D02B, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x40D55D, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x4200E1, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x420F49, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x421074, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x4214AF, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x4214E2, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x42194A, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x42197E, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x421991, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x421CE2, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x421D2A, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x421FC6, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x42205E, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x433121, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x43318F, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x492576, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x4925AA, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x4925E4, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x596251, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5996AA, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5996DE, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x599718, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x59E666, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x59E7EF, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x59E8CD, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x59EB1E, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x59EEE0, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x59EFB9, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x59F073, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x59F122, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x59F243, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x59FDD1, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x59FE4F, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x59FF1E, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x59FF9C, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A0248, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A0436, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A045C, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A2839, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A2D3B, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A2DB1, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A3C0A, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A3C8A, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A3CC2, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A3CF7, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A3D5A, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A3DAB, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A3DF9, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A3E3E, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A3E73, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A3EA8, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A3EDB, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A3F1B, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A3F54, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A3FB9, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A3FED, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A4023, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A407C, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A40B0, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A40E6, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A4126, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A415A, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A4190, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A41C9, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A41FF, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A4233, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A426A, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A42BA, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A42F3, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A4327, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A43E0, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A4419, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A444D, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A44AF, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A44E8, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A451C, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A457D, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A45B8, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A45EC, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A4BB1, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A4BC2, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A4C33, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A4C77, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A4CCF, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A4D11, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A4D53, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A4D9A, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A4DCE, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A4E0E, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A4E57, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A4E8F, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A4ECC, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A4F42, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A4F76, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A4FBB, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A4FEF, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A5031, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A506C, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A50A7, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A50EC, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A5127, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A5162, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A519D, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A51DA, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A5210, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A524B, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A529D, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A52D2, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A5306, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A5351, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A5394, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A5735, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A5769, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A57BE, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A57F2, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A5826, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A585F, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A5893, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A5926, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A5E4C, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A5EDF, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A61A1, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A61F7, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A622C, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A6278, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A65A0, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A65EE, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A6AD7, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A6B44, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A6D29, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A6D8C, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A6E18, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A6E64, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A6EF0, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A6F3C, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A6FC8, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A7014, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A70C9, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A714C, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A71E1, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A7264, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A732D, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A73FE, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A7813, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A7E31, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A7ED1, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A8A33, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A8A67, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A8A9C, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A8ACB, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A8B1F, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A8B81, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A8BE2, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A8F1B, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A8F5B, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A90FD, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A912E, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x5A9390, (DWORD)(&ItemDescriptionType));
	Memory::Update<DWORD>(0x40CD9E, (DWORD)(&ItemDescriptionType[1]));
	Memory::Update<DWORD>(0x5960CF, (DWORD)(&ItemDescriptionType[1]));
	Memory::Update<DWORD>(0x5A87AE, (DWORD)(&ItemDescriptionType[1]));
	Memory::Update<DWORD>(0x40CDB9, (DWORD)(&ItemDescriptionType[2]));
	Memory::Update<DWORD>(0x421447, (DWORD)(&ItemDescriptionType[2]));
	Memory::Update<DWORD>(0x5A8866, (DWORD)(&ItemDescriptionType[3]));
	Memory::Update<DWORD>(0x5A8945, (DWORD)(&ItemDescriptionType[3]));
	Memory::Update<DWORD>(0x5A8971, (DWORD)(&ItemDescriptionType[3]));
	Memory::Update<DWORD>(0x40D23F, (DWORD)(&ItemDescriptionType[4]));
	Memory::Update<DWORD>(0x5A888E, (DWORD)(&ItemDescriptionType[4]));
	Memory::Update<DWORD>(0x5A88B8, (DWORD)(&ItemDescriptionType[5]));
}

void Item::Add(BYTE Type, WORD Index, int Price, const std::vector<ItemEffectInfo>& Effects, BYTE Others)
{
	BYTE CorrectType;

	switch (Type)
	{
	case Crossbow:
		CorrectType = Bow;
		break;
	default:
		CorrectType = Type;
		break;
	}

	WORD Item = ITEM_GET(CorrectType, Index);

	try
	{
		switch (Type)
		{
		case Sword: // For Swords and Blades
		{
			this->Items[Item] = { Type, Others, FOLDER_ITEM, {}, Price, Effects };
			wsprintf(this->Items.at(Item).File, "Sword%02d", Index + 1);
			break;
		}
		case Axe: // For Axes
		{
			this->Items[Item] = { Type, Others, FOLDER_ITEM, {}, Price, Effects };
			wsprintf(this->Items.at(Item).File, "Axe%02d", Index + 1);
			break;
		}
		case Mace: // For Maces and Scepters
		{
			this->Items[Item] = { Type, Others, FOLDER_ITEM, {}, Price, Effects };
			wsprintf(this->Items.at(Item).File, "Mace%02d", Index + 1);
			break;
		}
		case Spear: // For Spears
		{
			this->Items[Item] = { Type, Others, FOLDER_ITEM, {}, Price, Effects };
			wsprintf(this->Items.at(Item).File, "Spear%02d", Index + 1);
			break;
		}
		case Bow:		// For Bows
		{
			this->Items[Item] = { Type, Others, FOLDER_ITEM, {}, Price, Effects };
			wsprintf(this->Items.at(Item).File, "Bow%02d", Index + 1);
			break;
		}
		case Crossbow:	// For Crossbows
		{
			this->Items[Item] = { Type, Others, FOLDER_ITEM, {}, Price, Effects };
			wsprintf(this->Items.at(Item).File, "CrossBow%02d", Index + 1);
			break;
		}
		case Staff: // For Staffs
		{
			this->Items[Item] = { Type, Others, FOLDER_ITEM, {}, Price, Effects };
			wsprintf(this->Items.at(Item).File, "Staff%02d", Index + 1);
			break;
		}
		case Shield: // For Shields
		{
			this->Items[Item] = { Type, Others, FOLDER_ITEM, {}, Price, Effects };
			wsprintf(this->Items.at(Item).File, "Shield%02d", Index + 1);
			break;
		}
		case Helm:
		{
			this->Items[Item] = { Type, Others, FOLDER_PLAYER, {}, Price, Effects };
			wsprintf(this->Items.at(Item).File, "HelmMale%02d", Index + 1);
			break;
		}
		case Armor:
		{
			this->Items[Item] = { Type, Others, FOLDER_PLAYER, {}, Price, Effects };
			wsprintf(this->Items.at(Item).File, "ArmorMale%02d", Index + 1);
			break;
		}
		case Pants:
		{
			this->Items[Item] = { Type, Others, FOLDER_PLAYER, {}, Price, Effects };
			wsprintf(this->Items.at(Item).File, "PantMale%02d", Index + 1);
			break;
		}
		case Gloves:
		{
			this->Items[Item] = { Type, Others, FOLDER_PLAYER, {}, Price, Effects };
			wsprintf(this->Items.at(Item).File, "GloveMale%02d", Index + 1);
			break;
		}
		case Boots:
		{
			this->Items[Item] = { Type, Others, FOLDER_PLAYER, {}, Price, Effects };
			wsprintf(this->Items.at(Item).File, "BootMale%02d", Index + 1);
			break;
		}
		case Wing:
		{
			this->Items[Item] = { Type, Others, FOLDER_ITEM, {}, Price, Effects };
			wsprintf(this->Items.at(Item).File, "Wing%02d", Index + 1);
			break;
		}
		case Jewel:
		{
			this->Items[Item] = { Type, Others, FOLDER_ITEM, {}, Price, Effects };
			wsprintf(this->Items.at(Item).File, "Jewel%02d", Index + 1);
			break;
		}
		default:
		{
			break;
		}
		}
	}
	catch (...)
	{
	}
}

ItemCustomInfo* Item::Get(WORD Index)
{
	if (this->Items.count(Index) > 0)
	{
		return &this->Items.at(Index);
	}

	return null;
}

bool Item::ApplyWingEffect(WORD Model, DWORD This, DWORD b, DWORD c, DWORD d)
{
	auto Item = this->Get(Model - ITEM_MODEL);

	if (Item && !Item->Effect.empty())
	{
		for (auto it = Item->Effect.begin(); it != Item->Effect.end(); ++it)
		{
			pGetEffectPosition(This, 48 * it->Bone + 0x689E82C, c, b, 1);

			switch (it->Index)
			{
			case 1478:
			case 1453:
			case 1452:
			case 1533:
			case 1551:
			case 1482:
			case 1579:
			case 1566:
			case 1493:
			case 1535:
			case 1477:
			case 1534:
			case 1498:
			case 1571:
			{
				pShowEffect1(it->Index, b, it->Size, it->Color, d, 0, 0);
				break;
			}
			default:
			{
				pShowEffect2(it->Index, b, d + 28, it->Color, it->Count, it->Size, 0);
				break;
			}
			}
		}

		return true;
	}

	return false;
}

void Item::SetGlow(int Model, float Alpha, DWORD Unk1, GlowColor* Color, DWORD Unk2)
{
	auto GlowColor = gItem.Glow.Get(Model);

	if (GlowColor)
	{
		memcpy(Color, GlowColor, sizeof(::GlowColor));
		return;
	}

	pSetGlow(Model, Alpha, Unk1, Color, Unk2);
}

void Item::SetDescription(ItemInfo* Item)
{
	auto Description = gItem.Description.Get(Item->Index);

	if (Description)
	{
		for (const auto& i : *Description)
		{
			strcpy_s(ItemDescription[pItemDescriptionCount], i.Text.c_str());
			ItemDescriptionType[pItemDescriptionCount] = i.Bold;
			ItemDescriptionColor[pItemDescriptionCount] = 200;
			CustomBackground[pItemDescriptionCount] = i.Background;
			CustomForeground[pItemDescriptionCount] = i.Foreground;

			++pItemDescriptionCount;
		}
	}
}

void Item::MakePreviewCharacter(int Index, BYTE* CharSet, int Address, int Mode)
{
	pMakePreviewCharacter(Index, CharSet, Address, Mode);

	ViewportInfo* Viewport = (Address) ? &(*(ViewportInfo*)(Address)) : gViewport.GetByPosition(Index);

	if (Viewport)
	{
		if ((CharSet[4] & 12) == 12 && CharSet[16] != 0)
		{
			Viewport->Wings = ITEM_GET_MODEL(12, CharSet[16] + 31);
		}
	}
}

void __declspec(naked) Item::SetDescriptionInfo()
{
	static DWORD Local = 0x5A7428;
	static ItemInfo* Info;

	__asm
	{
		PUSHAD;
		MOV Info, EDI;
	}

	gItem.SetDescription(Info);

	__asm
	{
		POPAD;
		MOV EAX, DWORD PTR DS : [0x788C850];
		LEA EAX, DWORD PTR DS : [EAX + EAX * 0x4];
		PUSH 0x6B8B64;
		JMP Local;
	}
}

void __declspec(naked) Item::SetDescriptionColor1()
{
	static DWORD Local[2] = { 0x59E794, 0x59E7EC };
	static DWORD Id, Current;
	static BYTE R, G, B;

	__asm
	{
		MOV EAX, DWORD PTR DS : [EDI * 0x4 + ItemDescriptionColor];
		PUSHAD;
		MOV Id, EAX;
		MOV Current, EDI;
	}

	if (Id == 200)
	{
		R = (BYTE)(CustomForeground[Current] & 0xFF);
		G = (BYTE)((CustomForeground[Current] & 0xFF00) >> 8);
		B = (BYTE)((CustomForeground[Current] & 0xFF0000) >> 16);

		glColor3f(R / 255.0f, G / 255.0f, B / 255.0f);

		pMessageBackgroundColor = CustomBackground[Current];
		pMessageForegroundColor = CustomForeground[Current];

		CustomBackground[Current] = 0;
		CustomForeground[Current] = 0;

		__asm
		{
			POPAD;
			JMP Local[4];
		}
	}

	__asm
	{
		POPAD;
		MOV EAX, DWORD PTR DS : [EDI * 0x4 + ItemDescriptionColor];
		JMP Local[0];
	}
}

void __declspec(naked) Item::SetDescriptionColor2()
{
	static DWORD Local[2] = { 0x59EBEE, 0x59EC46 };
	static DWORD Id, Current;
	static BYTE R, G, B;

	__asm
	{
		MOV EAX, DWORD PTR DS : [EBX * 0x4 + ItemDescriptionColor];
		PUSHAD;
		MOV Id, EAX;
		MOV Current, EBX;
	}

	if (Id == 200)
	{
		R = (BYTE)(CustomForeground[Current] & 0xFF);
		G = (BYTE)((CustomForeground[Current] & 0xFF00) >> 8);
		B = (BYTE)((CustomForeground[Current] & 0xFF0000) >> 16);

		glColor3f(R / 255.0f, G / 255.0f, B / 255.0f);

		pMessageBackgroundColor = CustomBackground[Current];
		pMessageForegroundColor = CustomForeground[Current];

		CustomBackground[Current] = 0;
		CustomForeground[Current] = 0;

		__asm
		{
			POPAD;
			JMP Local[4];
		}
	}

	__asm
	{
		POPAD;
		JMP Local[0];
	}
}

void __declspec(naked) Item::NewWings1()
{
	static DWORD Local[2] = { 0x540ABC, 0x540A9E };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		CMP AX, 0x1806;
		JLE LessOrEqual;
		MOV Id, AX;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Type == Item::Wing)
	{
		__asm
		{
			POPAD;
			JMP LessOrEqual;
		}
	}

	__asm
	{
		POPAD;
		JMP Local[4];

	LessOrEqual:
		JMP Local[0];
	}
}

void __declspec(naked) Item::NewWings2()
{
	static DWORD Local[2] = { 0x540EE1, 0x540ECC };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		CMP AX, 0x1806;
		JG Greater;

	Equal:
		JMP Local[4];

	Greater:
		MOV Id, AX;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Type == Item::Wing)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		JMP Local[0];
	}
}

void __declspec(naked) Item::NewWings3()
{
	static DWORD Local[2] = { 0x540FAF, 0x540FAA };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		CMP DX, 0x1806;
		JG Greater;

	Equal:
		JMP Local[4];

	Greater:
		MOV Id, DX;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Type == Item::Wing)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		JMP Local[0];
	}
}

void __declspec(naked) Item::NewWings4()
{
	static DWORD Local[2] = { 0x54130E, 0x54125D };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		CMP CX, 0x1806;
		JG Greater;

	Equal:
		JMP Local[4];

	Greater:
		MOV Id, CX;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Type == Item::Wing)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		JMP Local[0];
	}
}

void __declspec(naked) Item::NewWings5()
{
	static DWORD Local[2] = { 0x5414CF, 0x5414BE };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		CMP AX, 0x1806;
		JG Greater;

	Equal:
		JMP Local[4];

	Greater:
		MOV Id, AX;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Type == Item::Wing)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		JMP Local[0];
	}
}

void __declspec(naked) Item::NewWings6()
{
	static DWORD Local[6] = { 0x541726, 0x5416E9, 0x5416CD, 0x541709, 0x54172C, 0x5416DB };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		MOV Id, AX;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Type == Item::Wing)
	{
		if (Value->Subtype == 1)
		{
			__asm
			{
				POPAD;
				JMP Local[4];
			}
		}
		else if (Value->Subtype == 2)
		{
			__asm
			{
				POPAD;
				JMP Local[8];
			}
		}
		else if (Value->Subtype == 3)
		{
			__asm
			{
				POPAD;
				JMP Local[12];
			}
		}
		else if (Value->Subtype == 4)
		{
			__asm
			{
				POPAD;
				JMP Local[16];
			}
		}
		else
		{
			__asm
			{
				POPAD;
				JMP Local[20];
			}
		}

		__asm
		{
			POPAD;
			JMP NotZero;
		}
	}

	__asm
	{
		POPAD;
		CMP AX, 0x1806;
		JNZ NotZero;
		JMP Local[12];

	NotZero:
		JMP Local[0];
	}
}

void __declspec(naked) Item::NewWings7()
{
	static DWORD Local[2] = { 0x54244B, 0x54224A };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		CMP CX, 0x1806;
		JG Greater;

	Equal:
		JMP Local[4];

	Greater:
		MOV Id, CX;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Type == Item::Wing)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		JMP Local[0];
	}
}

void __declspec(naked) Item::NewWings8()
{
	static DWORD Local[2] = { 0x5422A0, 0x542299 };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		CMP CX, 0x1806;
		JLE LessOrEqual;
		MOV Id, CX;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Type == Item::Wing)
	{
		__asm
		{
			POPAD;
			JMP LessOrEqual;
		}
	}

	__asm
	{
		POPAD;
		JMP Local[4];

	LessOrEqual:
		JMP Local[0];
	}
}

void __declspec(naked) Item::NewWings9()
{
	static DWORD Local[2] = { 0x542373, 0x54239E };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		CMP WORD PTR SS : [EBP - 0x14], 0x1806;
		JG Greater;

	Equal:
		JMP Local[0];

	Greater:
		XOR EDX, EDX;
		MOVZX EDX, WORD PTR SS : [EBP - 0x14];
		MOV Id, DX;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Type == Item::Wing)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewWings10()
{
	static DWORD Local[2] = { 0x542B00, 0x542D1D };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		CMP DI, 0x1806;
		JG Greater;

	Equal:
		JMP Local[0];

	Greater:
		MOV Id, DI;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Type == Item::Wing)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewWings11()
{
	static DWORD Local[2] = { 0x542B56, 0x542B6B };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		CMP DI, 0x1806;
		JG Greater;

	Equal:
		JMP Local[0];

	Greater:
		MOV Id, DI;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Type == Item::Wing)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewWings12()
{
	static DWORD Local[2] = { 0x542C07, 0x542C72 };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		CMP WORD PTR DS : [EBX], 0x1806;
		JG Greater;

	Equal:
		JMP Local[0];

	Greater:
		XOR EAX, EAX;
		MOVZX EAX, WORD PTR DS : [EBX];
		MOV Id, AX;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Type == Item::Wing)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewWings13()
{
	static DWORD Local[2] = { 0x542D9B, 0x542DFC };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		CMP AX, 0x1806;
		JLE LessOrEqual;
		MOV Id, AX;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Type == Item::Wing)
	{
		__asm
		{
			POPAD;
			JMP LessOrEqual;
		}
	}

	__asm
	{
		POPAD;
		JMP Local[0];

	LessOrEqual:
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewWings14()
{
	static DWORD Local[2] = { 0x58A071, 0x58A0E1 };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		CMP AX, 0x1806;
		JLE LessOrEqual;
		MOV Id, AX;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Type == Item::Wing)
	{
		__asm
		{
			POPAD;
			JMP LessOrEqual;
		}
	}

	__asm
	{
		POPAD;
		JMP Local[0];

	LessOrEqual:
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewWings15()
{
	static DWORD Local[2] = { 0x5A1388, 0x5A13B3 };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		CMP DX, 0x1806;
		JLE LessOrEqual;
		MOV Id, DX;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Type == Item::Wing)
	{
		__asm
		{
			POPAD;
			JMP LessOrEqual;
		}
	}

	__asm
	{
		POPAD;
		JMP Local[0];

	LessOrEqual:
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewWings16()
{
	static DWORD Local[2] = { 0x5A191E, 0x5A1950 };
	static DWORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		CMP EAX, 0x1806;
		JG Greater;

	Equal:
		JMP Local[0];

	Greater:
		MOV Id, EAX;
		PUSHAD;
	}

	Value = gItem.Get((WORD)(Id));

	if (Value && Value->Type == Item::Wing)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewWings17()
{
	static DWORD Local[2] = { 0x5A2389, 0x5A2390 };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		CMP CX, 0x1806;
		JLE LessOrEqual;
		MOV Id, CX;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Type == Item::Wing)
	{
		__asm
		{
			POPAD;
			JMP LessOrEqual;
		}
	}

	__asm
	{
		POPAD;
		JMP Local[0];

	LessOrEqual:
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewWings18()
{
	static DWORD Local[2] = { 0x5A394C, 0x5A3970 };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		CMP CX, 0x1806;
		JG Greater;

	Equal:
		JMP Local[0];

	Greater:
		MOV Id, CX;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Type == Item::Wing)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewWings19()
{
	static DWORD Local[2] = { 0x5A531E, 0x5A5361 };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		CMP CX, 0x1806;
		JG Greater;

	Equal:
		JMP Local[0];

	Greater:
		MOV Id, CX;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Type == Item::Wing)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewWings20()
{
	static DWORD Local[2] = { 0x5A5FFF, 0x5A6006 };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		CMP CX, 0x1806;
		JG Greater;

	Equal:
		JMP Local[0];

	Greater:
		MOV Id, CX;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Type == Item::Wing)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewWings21()
{
	static DWORD Local[2] = { 0x5A770E, 0x5A7714 };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		CMP AX, 0x1806;
		JLE LessOrEqual;
		MOV Id, AX;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Type == Item::Wing)
	{
		__asm
		{
			POPAD;
			JMP LessOrEqual;
		}
	}

	__asm
	{
		POPAD;
		JMP Local[0];

	LessOrEqual:
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewWings22()
{
	static DWORD Local[2] = { 0x5A7D7E, 0x5A7D85 };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		CMP CX, 0x1806;
		JLE LessOrEqual;
		MOV Id, CX;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Type == Item::Wing)
	{
		__asm
		{
			POPAD;
			JMP LessOrEqual;
		}
	}

	__asm
	{
		POPAD;
		JMP Local[0];

	LessOrEqual:
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewWings23()
{
	static DWORD Local[2] = { 0x5AB4B0, 0x5AB4D7 };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		CMP AX, 0x1806;
		JLE LessOrEqual;
		MOV Id, AX;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Type == Item::Wing)
	{
		__asm
		{
			POPAD;
			JMP LessOrEqual;
		}
	}

	__asm
	{
		POPAD;
		JMP Local[0];

	LessOrEqual:
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewWings24()
{
	static DWORD Local[2] = { 0x5B1849, 0x5B184F };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		CMP AX, 0x1806;
		JLE LessOrEqual;
		MOV Id, AX;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Type == Item::Wing)
	{
		__asm
		{
			POPAD;
			JMP LessOrEqual;
		}
	}

	__asm
	{
		POPAD;
		JMP Local[0];

	LessOrEqual:
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewWings25()
{
	static DWORD Local[2] = { 0x5B188B, 0x5B2688 };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		CMP CX, 0x1806;
		JLE LessOrEqual;
		MOV Id, CX;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Type == Item::Wing)
	{
		__asm
		{
			POPAD;
			JMP LessOrEqual;
		}
	}

	__asm
	{
		POPAD;
		JMP Local[0];

	LessOrEqual:
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewWings26()
{
	static DWORD Local[2] = { 0x5C6D2F, 0x5C6D3C };
	static DWORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		CMP ESI, 0x1806;
		JLE LessOrEqual;
		MOV Id, ESI;
		PUSHAD;
	}

	Value = gItem.Get((WORD)(Id));

	if (Value && Value->Type == Item::Wing)
	{
		__asm
		{
			POPAD;
			JMP LessOrEqual;
		}
	}

	__asm
	{
		POPAD;
		JMP Local[0];

	LessOrEqual:
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewWings27()
{
	static DWORD Local[2] = { 0x5CD788, 0x5CDE0D };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		CMP CX, 0x1806;
		JLE LessOrEqual;
		MOV Id, CX;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Type == Item::Wing)
	{
		__asm
		{
			POPAD;
			JMP LessOrEqual;
		}
	}

	__asm
	{
		POPAD;
		JMP Local[0];

	LessOrEqual:
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewWings28()
{
	static DWORD Local[2] = { 0x5CDE95, 0x5CF0DE };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		CMP CX, 0x1806;
		JLE LessOrEqual;
		MOV Id, CX;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Type == Item::Wing)
	{
		__asm
		{
			POPAD;
			JMP LessOrEqual;
		}
	}

	__asm
	{
		POPAD;
		JMP Local[0];

	LessOrEqual:
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewWings29()
{
	static DWORD Local[2] = { 0x5EBB77, 0x5EBB7D };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		CMP AX, 0x1806;
		JLE LessOrEqual;
		MOV Id, AX;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Type == Item::Wing)
	{
		__asm
		{
			POPAD;
			JMP LessOrEqual;
		}
	}

	__asm
	{
		POPAD;
		JMP Local[0];

	LessOrEqual:
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewWings30()
{
	static DWORD Local[2] = { 0x5EBE02, 0x5EBE0A };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		CMP AX, 0x1806;
		JG Greater;

	Equal:
		JMP Local[0];

	Greater:
		MOV Id, AX;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Type == Item::Wing)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewWings31()
{
	static DWORD Local[6] = { 0x5D043A, 0x5D0482, 0x5D043C, 0x5D04A2, 0x5D0188, 0x5D045F };
	static DWORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		MOV Id, ESI;
		PUSHAD;
	}

	Value = gItem.Get((WORD)(Id));

	if (Value && Value->Type == Item::Wing)
	{
		if (Value->Subtype == 1)
		{
			__asm
			{
				POPAD;
				JMP Local[4];
			}
		}
		else if (Value->Subtype == 2)
		{
			__asm
			{
				POPAD;
				JMP Local[8];
			}
		}
		else if (Value->Subtype == 3)
		{
			__asm
			{
				POPAD;
				JMP Local[12];
			}
		}
		else if (Value->Subtype == 4)
		{
			__asm
			{
				POPAD;
				JMP Local[16];
			}
		}
		else
		{
			__asm
			{
				POPAD;
				JMP Local[20];
			}
		}
	}

	__asm
	{
		POPAD;
		CMP ESI, 0x1803;
		JMP Local[0];
	}
}

void __declspec(naked) Item::NewWings32()
{
	static DWORD Local[2] = { 0x5AA361, 0x5AA347 };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		CMP AX, 0x1A09;
		JLE LessOrEqual;
		MOV Id, AX;
		PUSHAD;
	}

	Value = gItem.Get(Id - ITEM_MODEL);

	if (Value && Value->Type == Item::Wing)
	{
		__asm
		{
			POPAD;
			JMP LessOrEqual;
		}
	}

	__asm
	{
		POPAD;
		JMP Local[4];

	LessOrEqual:
		JMP Local[0];
	}
}

void __declspec(naked) Item::NewWings33()
{
	static DWORD Local[2] = { 0x5F9E4A, 0x5F9DE7 };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		CMP AX, 0x1A09;
		JLE LessOrEqual;
		MOV Id, AX;
		PUSHAD;
	}

	Value = gItem.Get(Id - ITEM_MODEL);

	if (Value && Value->Type == Item::Wing)
	{
		__asm
		{
			POPAD;
			JMP LessOrEqual;
		}
	}

	__asm
	{
		POPAD;
		JMP Local[4];

	LessOrEqual:
		JMP Local[0];
	}
}

void __declspec(naked) Item::NewWings34()
{
	static DWORD Local[2] = { 0x5F892C, 0x5F8754 };
	static DWORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		MOV Id, ECX;
		PUSHAD;
	}

	Value = gItem.Get((WORD)(Id - ITEM_MODEL));

	if (Value && Value->Type == Item::Wing)
	{
		__asm
		{
			POPAD;
			JMP Local[0];
		}
	}

	__asm
	{
		POPAD;
		CMP ECX, 0x1A09;
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewWings35()
{
	static DWORD Local[2] = { 0x540FDB, 0x540FCC };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		MOV Id, DX;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Type == Item::Wing)
	{
		__asm
		{
			POPAD;
			JMP Local[0];
		}
	}

	__asm
	{
		POPAD;
		CMP DX, 0x1807;
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewWings36()
{
	static DWORD Local[2] = { 0x540FF5, 0x540FEC };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		MOV Id, DX;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Type == Item::Wing)
	{
		__asm
		{
			POPAD;
			JMP Local[0];
		}
	}

	__asm
	{
		POPAD;
		CMP DX, 0x1807;
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewWings37()
{
	static DWORD Local[2] = { 0x541AA8, 0x541AB2 };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		MOV Id, AX;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Type == Item::Wing)
	{
		__asm
		{
			POPAD;
			JMP Local[0];
		}
	}

	__asm
	{
		POPAD;
		CMP AX, 0x1807;
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewJewels1()
{
	static DWORD Local[2] = { 0x5B8E6B, 0x5B8E92 };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		MOV Id, SI;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Type == Jewel)
	{
		__asm
		{
			POPAD;
			JMP Local[4];
		}
	}

	__asm
	{
		POPAD;
		CMP SI, 0x1C0D;
		JMP Local[0];
	}
}

void __declspec(naked) Item::NewJewels2()
{
	static DWORD Local[2] = { 0x541DA4, 0x542518 };
	static WORD Id;
	static ItemCustomInfo* Value;
	static DWORD Price;

	__asm
	{
		MOV Id, CX;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Price >= 0)
	{
		Price = Value->Price;

		__asm
		{
			POPAD;
			MOV DWORD PTR SS : [EBP - 0x14], ECX;
			MOV ESI, Price;
			JMP Local[4];
		}
	}

	__asm
	{
		POPAD;
		CMP CX, 0x1C0D;
		JMP Local[0];
	}
}

void __declspec(naked) Item::NewJewels3()
{
	static DWORD Local[2] = { 0x5F88A8, 0x5F87DB };
	static DWORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		MOV Id, ECX;
		PUSHAD;
	}

	Value = gItem.Get((WORD)(Id - ITEM_MODEL));

	if (Value && Value->Type == Jewel)
	{
		__asm
		{
			POPAD;
			JMP Local[4];
		}
	}

	__asm
	{
		POPAD;
		CMP CX, 0x1E22;
		JMP Local[0];
	}
}

void __declspec(naked) Item::NewJewels4()
{
	static DWORD Local[2] = { 0x5C6CF0, 0x5C6D04 };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		MOV Id, DX;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Type == Jewel)
	{
		__asm
		{
			POPAD;
			JMP Local[4];
		}
	}

	__asm
	{
		POPAD;
		CMP DX, 0x1C0D;
		JMP Local[0];
	}
}

void __declspec(naked) Item::NewBows1()
{
	static DWORD Local[2] = { 0x5CF24F, 0x5CF274 };
	static DWORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		MOV Id, ESI;
		PUSHAD;
	}

	Value = gItem.Get((WORD)(Id - ITEM_MODEL));

	if (Value && Value->Type == Bow)
	{
		__asm
		{
			POPAD;
			JMP Local[0];
		}
	}

	__asm
	{
		POPAD;
		CMP ESI, 0xA18;
		JNZ NotZero;
		JMP Local[0];

	NotZero:
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewBows2()
{
	static DWORD Local[2] = { 0x4EB659, 0x4EB6A0 };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		MOV Id, CX;
		PUSHAD;
	}

	Value = gItem.Get(Id - ITEM_MODEL);

	if (Value && Value->Type == Bow)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		CMP CX, 0xA18;
		JE Equal;
		JMP Local[0];

	Equal:
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewBows3()
{
	static DWORD Local[2] = { 0x4EA973, 0x4EA9BB };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		MOV Id, CX;
		PUSHAD;
	}

	Value = gItem.Get(Id - ITEM_MODEL);

	if (Value && Value->Type == Bow)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		CMP CX, 0xA18;
		JE Equal;
		JMP Local[0];

	Equal:
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewBows4()
{
	static DWORD Local[2] = { 0x5048FA, 0x504936 };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		MOV Id, DI;
		PUSHAD;
	}

	Value = gItem.Get(Id - ITEM_MODEL);

	if (Value && Value->Type == Bow)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		CMP DI, 0xA18;
		JE Equal;
		JMP Local[0];

	Equal:
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewBows5()
{
	static DWORD Local[2] = { 0x4EC5D1, 0x4EC626 };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		MOV Id, CX;
		PUSHAD;
	}

	Value = gItem.Get(Id - ITEM_MODEL);

	if (Value && Value->Type == Bow)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		CMP CX, 0xA18;
		JE Equal;
		JMP Local[0];

	Equal:
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewBows6()
{
	static DWORD Local[2] = { 0x4EC842, 0x4EC8CE };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		MOV Id, CX;
		PUSHAD;
	}

	Value = gItem.Get(Id - ITEM_MODEL);

	if (Value && Value->Type == Bow)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		CMP CX, 0xA18;
		JE Equal;
		JMP Local[0];

	Equal:
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewBows7()
{
	static DWORD Local[2] = { 0x555F6E, 0x555FF4 };
	static DWORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		MOV Id, EBX;
		PUSHAD;
	}

	Value = gItem.Get((WORD)(Id));

	if (Value && Value->Type == Bow)
	{
		__asm
		{
			POPAD;
			JMP Local[0];
		}
	}

	__asm
	{
		POPAD;
		CMP EBX, 0x815;
		JNZ NotZero;
		JMP Local[0];

	NotZero:
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewBows8()
{
	static DWORD Local[2] = { 0x54C3F8, 0x54C41F };
	static DWORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		MOV Id, ESI;
		PUSHAD;
	}

	Value = gItem.Get((WORD)(Id));

	if (Value && Value->Type == Bow)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		CMP ESI, 0x815;
		JE Equal;
		JMP Local[0];

	Equal:
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewBows9()
{
	static DWORD Local[2] = { 0x543AEF, 0x543AFC };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		MOV Id, BX;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Type == Bow)
	{
		__asm
		{
			POPAD;
			JMP Local[0];
		}
	}

	__asm
	{
		POPAD;
		CMP BX, 0x815;
		JNZ NotZero;
		JMP Local[0];

	NotZero:
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewBows10()
{
	static DWORD Local[2] = { 0x5A8120, 0x5A8148 };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		MOV Id, AX;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Type == Bow)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		CMP AX, 0x815;
		JE Equal;
		JMP Local[0];

	Equal:
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewBows11()
{
	static DWORD Local[2] = { 0x559312, 0x559319 };
	static DWORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		MOV Id, EAX;
		PUSHAD;
	}

	Value = gItem.Get((WORD)(Id));

	if (Value && Value->Type == Bow)
	{
		__asm
		{
			POPAD;
			JMP Local[0];
		}
	}

	__asm
	{
		POPAD;
		CMP EAX, 0x815;
		JNZ NotZero;
		JMP Local[0];

	NotZero:
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewBows12()
{
	static DWORD Local[2] = { 0x58D596, 0x58D5B2 };
	static DWORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		MOV Id, EAX;
		PUSHAD;
	}

	Value = gItem.Get((WORD)(Id));

	if (Value && Value->Type == Bow)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		CMP EAX, 0x815;
		JE Equal;
		JMP Local[0];

	Equal:
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewBows13()
{
	static DWORD Local[2] = { 0x555BFC, 0x555C67 };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		MOV Id, CX;
		PUSHAD;
	}

	Value = gItem.Get(Id);

	if (Value && Value->Type == Bow)
	{
		__asm
		{
			POPAD;
			JMP Local[0];
		}
	}

	__asm
	{
		POPAD;
		CMP CX, 0x815;
		JNZ NotZero;
		JMP Local[0];

	NotZero:
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewBows14()
{
	static DWORD Local[2] = { 0x54C05A, 0x54C083 };
	static DWORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		MOV Id, ESI;
		PUSHAD;
	}

	Value = gItem.Get((WORD)(Id));

	if (Value && Value->Type == Bow)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		CMP ESI, 0x815;
		JE Equal;
		JMP Local[0];

	Equal:
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewBows15()
{
	static DWORD Local[2] = { 0x57259A, 0x5725A8 };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		MOV Id, AX;
		PUSHAD;
	}

	Value = gItem.Get(Id - ITEM_MODEL);

	if (Value && Value->Type == Bow)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		CMP AX, 0xA18;
		JE Equal;
		JMP Local[0];

	Equal:
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewBows16()
{
	static DWORD Local[2] = { 0x570D31, 0x570D47 };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		MOV Id, AX;
		PUSHAD;
	}

	Value = gItem.Get(Id - ITEM_MODEL);

	if (Value && Value->Type == Bow)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		CMP AX, 0xA18;
		JE Equal;
		JMP Local[0];

	Equal:
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewCrossbows1()
{
	static DWORD Local[2] = { 0x4EC5F3, 0x4EC3A5 };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		MOV Id, AX;
		PUSHAD;
	}

	Value = gItem.Get(Id - ITEM_MODEL);

	if (Value && Value->Type == Crossbow)
	{
		__asm
		{
			POPAD;
			JMP Local[0];
		}
	}

	__asm
	{
		POPAD;
		CMP AX, 0xA15;
		JL Less;
		JMP Local[0];

	Less:
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewCrossbows2()
{
	static DWORD Local[2] = { 0x4EC867, 0x4EC877 };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		MOV Id, AX;
		PUSHAD;
	}

	Value = gItem.Get(Id - ITEM_MODEL);

	if (Value && Value->Type == Crossbow)
	{
		__asm
		{
			POPAD;
			JMP Local[0];
		}
	}

	__asm
	{
		POPAD;
		CMP AX, 0xA15;
		JL Less;
		JMP Local[0];

	Less:
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewCrossbows3()
{
	static DWORD Local[2] = { 0x533835, 0x533985 };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		MOV Id, DX;
		PUSHAD;
	}

	Value = gItem.Get(Id - ITEM_MODEL);

	if (Value && Value->Type == Crossbow)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		CMP DX, 0xA15;
		JE Equal;
		JMP Local[0];

	Equal:
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewCrossbows4()
{
	static DWORD Local[2] = { 0x4EB677, 0x4EB684 };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		MOV Id, AX;
		PUSHAD;
	}

	Value = gItem.Get(Id - ITEM_MODEL);

	if (Value && Value->Type == Crossbow)
	{
		__asm
		{
			POPAD;
			JMP Local[0];
		}
	}

	__asm
	{
		POPAD;
		CMP AX, 0xA15;
		JL Less;
		JMP Local[0];

	Less:
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewCrossbows5()
{
	static DWORD Local[2] = { 0x4C58DA, 0x4C5940 };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		MOV Id, AX;
		PUSHAD;
	}

	Value = gItem.Get(Id - ITEM_MODEL);

	if (Value && Value->Type == Crossbow)
	{
		__asm
		{
			POPAD;
			JMP Local[0];
		}
	}

	__asm
	{
		POPAD;
		CMP AX, 0xA15;
		JL Less;
		JMP Local[0];

	Less:
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewCrossbows6()
{
	static DWORD Local[2] = { 0x5F54C7, 0x5F54DA };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		MOV Id, CX;
		PUSHAD;
	}

	Value = gItem.Get(Id - ITEM_MODEL);

	if (Value && Value->Type == Crossbow)
	{
		__asm
		{
			POPAD;
			JMP Local[0];
		}
	}

	__asm
	{
		POPAD;
		CMP CX, 0xA15;
		JL Less;
		JMP Local[0];

	Less:
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewCrossbows7()
{
	static DWORD Local[2] = { 0x504924, 0x50492F };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		MOV Id, CX;
		PUSHAD;
	}

	Value = gItem.Get(Id - ITEM_MODEL);

	if (Value && Value->Type == Crossbow)
	{
		__asm
		{
			POPAD;
			JMP Local[0];
		}
	}

	__asm
	{
		POPAD;
		CMP CX, 0xA15;
		JL Less;
		JMP Local[0];

	Less:
		JMP Local[4];
	}
}

void __declspec(naked) Item::NewCrossbows8()
{
	static DWORD Local[2] = { 0x5001A7, 0x5001B1 };
	static DWORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		MOV Id, EDI;
		PUSHAD;
	}

	Value = gItem.Get((WORD)(Id - ITEM_MODEL));

	if (Value && Value->Type == Crossbow)
	{
		__asm
		{
			POPAD;
			JMP Local[4];
		}
	}

	__asm
	{
		POPAD;
		CMP EDI, 0xA15;
		JMP Local[0];
	}
}

void __declspec(naked) Item::NewCrossbows9()
{
	static DWORD Local[2] = { 0x4EA99F, 0x4EA991 };
	static WORD Id;
	static ItemCustomInfo* Value;

	__asm
	{
		MOV Id, AX;
		PUSHAD;
	}

	Value = gItem.Get(Id - ITEM_MODEL);

	if (Value && Value->Type == Crossbow)
	{
		__asm
		{
			POPAD;
			JMP Local[4];
		}
	}

	__asm
	{
		POPAD;
		CMP AX, 0xA15;
		JL Less;
		JMP Local[4];

	Less:
		JMP Local[0];
	}
}

void __declspec(naked) Item::MultipleShotSkillEffect()
{
	static DWORD Local[11] = { 0x533495, 0x5334BE, 0x5334E7, 0x533510, 0x533539, 0x533562, 0x53358B, 0x5335B1, 0x5335D7, 0x5335FD, 0x533485 };
	static DWORD Item1;
	static DWORD Item2;
	static ItemCustomInfo* Value;
	static bool Effect = false;

	__asm
	{
		MOV Effect, 0;
		MOV Item1, EDX;
		MOV Item2, ECX;
		ADD ECX, -0xA0B;
		PUSHAD;
	}

	Value = gItem.Get((WORD)(Item1));

	if (Value && Value->Type == Bow)
	{
		Effect = true;
	}

	if (!Effect)
	{
		Value = gItem.Get((WORD)(Item2 - ITEM_MODEL));

		if (Value && Value->Type == Crossbow)
		{
			Effect = true;
		}
	}

	if (Effect)
	{
		if (Value->Subtype == 0)
		{
			__asm
			{
				POPAD;
				JMP Local[0];
			}
		}
		else if (Value->Subtype == 1)
		{
			__asm
			{
				POPAD;
				JMP Local[4];
			}
		}
		else if (Value->Subtype == 2)
		{
			__asm
			{
				POPAD;
				JMP Local[8];
			}
		}
		else if (Value->Subtype == 3)
		{
			__asm
			{
				POPAD;
				JMP Local[12];
			}
		}
		else if (Value->Subtype == 4)
		{
			__asm
			{
				POPAD;
				JMP Local[16];
			}
		}
		else if (Value->Subtype == 5)
		{
			__asm
			{
				POPAD;
				JMP Local[20];
			}
		}
		else if (Value->Subtype == 6)
		{
			__asm
			{
				POPAD;
				JMP Local[24];
			}
		}
		else if (Value->Subtype == 7)
		{
			__asm
			{
				POPAD;
				JMP Local[28];
			}
		}
		else if (Value->Subtype == 8)
		{
			__asm
			{
				POPAD;
				JMP Local[32];
			}
		}
		else if (Value->Subtype == 9)
		{
			__asm
			{
				POPAD;
				JMP Local[36];
			}
		}
	}

	__asm
	{
		POPAD;
		JMP Local[40];
	}
}

void __declspec(naked) Item::SingleShotSkillEffect()
{
	static DWORD Local[7] = { 0x53364D, 0x533680, 0x5336B3, 0x5336E6, 0x533719, 0x53374C, 0x533635 };
	static DWORD Item1;
	static DWORD Item2;
	static ItemCustomInfo* Value;
	static bool Effect = false;

	__asm
	{
		MOV Effect, 0;
		MOV ECX, DWORD PTR SS : [EBP + 0x8];
		MOV Item2, ECX;
		LEA ECX, DWORD PTR DS : [EDX - 0xA03];
		MOV Item1, EDX;
		PUSHAD;
	}

	Value = gItem.Get((WORD)(Item1 - ITEM_MODEL));

	if (Value && Value->Type == Bow)
	{
		Effect = true;
	}

	if (!Effect)
	{
		Value = gItem.Get((WORD)(Item2 - ITEM_MODEL));

		if (Value && Value->Type == Crossbow)
		{
			Effect = true;
		}
	}

	if (Effect)
	{
		if (Value->Subtype >= 0 && Value->Subtype <= 4)
		{
			__asm
			{
				POPAD;
				JMP Local[0];
			}
		}
		else if (Value->Subtype == 5)
		{
			__asm
			{
				POPAD;
				JMP Local[4];
			}
		}
		else if (Value->Subtype == 6)
		{
			__asm
			{
				POPAD;
				JMP Local[8];
			}
		}
		else if (Value->Subtype == 7)
		{
			__asm
			{
				POPAD;
				JMP Local[12];
			}
		}
		else if (Value->Subtype == 8)
		{
			__asm
			{
				POPAD;
				JMP Local[16];
			}
		}
		else if (Value->Subtype == 9)
		{
			__asm
			{
				POPAD;
				JMP Local[20];
			}
		}
	}

	__asm
	{
		POPAD;
		JMP Local[24];
	}
}

void __declspec(naked) Item::WingEffect()
{
	static DWORD Local[2] = { 0x5024C0, 0x50077A };
	static DWORD Model;
	static DWORD a, b, c, d;
	bool SetWingEffect(WORD Model, DWORD a, DWORD b, DWORD c, DWORD d);

	__asm
	{
		MOV DWORD PTR SS : [EBP + 0x28], EDX;
		FILD DWORD PTR SS : [EBP + 0x28];
		FMUL DWORD PTR DS : [0x6A79C0];
		FSTP DWORD PTR SS : [EBP + 0x28];
		MOV d, EBX;
		LEA EAX, DWORD PTR SS : [EBP - 0x18];
		MOV c, EAX;
		LEA EAX, DWORD PTR SS : [EBP - 0x24];
		MOV b, EAX;
		MOV a, ESI;
		MOV Model, EDI;
		PUSHAD;
	}

	if (gItem.ApplyWingEffect((WORD)(Model), a, b, c, d))
	{
		__asm
		{
			POPAD;
			JMP Local[0];
		}
	}

	__asm
	{
		POPAD;
		CMP EDI, 0x222;
		JMP Local[4];
	}
}

void __declspec(naked) Item::GlowEffect()
{
	static DWORD Local[4] = { 0x5F9D77, 0x5F9D77, 0x5F99B1, 0x5F9C65 };
	static WORD Id;
	static ItemCustomInfo* Value;
	static DWORD Level;
	static BYTE Excellent;

	__asm
	{
		MOV Level, EBX;
		PUSHAD;
		XOR EAX, EAX;
		MOV AX, WORD PTR DS : [ESI + 0x2];
		MOV Id, AX;
		MOV AL, BYTE PTR SS : [EBP + 0x1C];
		MOV Excellent, AL;
	}

	Value = gItem.Get((WORD)(Id - ITEM_MODEL));

	if (Value && Value->Type == Wing)
	{
		__asm
		{
			POPAD;
			JMP Local[0];
		}
	}

	__asm
	{
		POPAD;
		CMP EBX, 0x3;
		JL Less;
		JMP Local[8];

	Less:
		JMP Local[4];
	}
}

Item gItem;