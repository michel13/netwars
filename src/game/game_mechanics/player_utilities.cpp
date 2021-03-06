#include "player_utilities.h"

using namespace aw;

//After a player has build a unit, he participates until all units are defeated or the hq is captured.
//If the hq is captured, all units of the player will be destroyed.
game_mechanics::defeat_type game_mechanics::beaten(const map::ptr &map, const player::ptr &player)
{
	bool has_hq = false;
	bool has_units = false;

	for(int x = 0; x < map->width(); x++)
	{
		for(int y = 0; y < map->height(); y++)
		{
			const unit::ptr u = map->get_unit(coord(x, y));
			const terrain::ptr t = map->get_terrain(coord(x, y));

			if(u && player->his_unit(u))
				has_units = true;

			if(t && t->is_building() && player->his_building(t) && t->type() == terrain::HEADQUARTER)
				has_hq = true;
		}
	}

	if(player->has_units() && !has_units)
		return ALL_UNITS_BEATEN;

	if(!has_hq)
		return HQ_CAPTURED;

	return NOT_BEATEN;
}

//A player participates if he has a hq, and a unit or a base where he can produce units
bool game_mechanics::participates(const map::ptr &map, player::colors c)
{
	const player player(c);

	bool has_hq = false;
	bool has_base = false;
	bool has_units = false;

	for(int x = 0; x < map->width(); x++)
	{
		for(int y = 0; y < map->height(); y++)
		{
			terrain::ptr t = map->get_terrain(coord(x, y));
			if(t && t->is_building() && player.his_building(t))
			{
				if(t->type() == terrain::HEADQUARTER)
					has_hq = true;
				else if(t->type() == terrain::BASE)
					has_base = true;
			}

			const unit::ptr u = map->get_unit(coord(x, y));
			if(u && player.his_unit(u))
				has_units = true;
		}
	}

	return (has_hq && (has_base || has_units));
}

player::colors game_mechanics::color_from_string(const std::string& c) {
  if(c == "red")
	return player::RED;
  else if(c == "blue")
	return player::BLUE;
  else if(c == "greeen")
	return player::GREEN;
  else if(c == "yellow")
	return player::YELLOW;
  else if(c == "black")
	return player::BLACK;
  else
	throw std::runtime_error("Unknown color: " + c);
}

std::string game_mechanics::color_to_string(player::colors c) {
  switch(c) {
  case player::RED:
	  return "red";
  case player::BLUE:
	return "blue";
  case player::GREEN:
	return "green";
  case player::YELLOW:
	return "yellow";
  case player::BLACK:
	return "black";
  default:
	return "UNDEFINED";
  }
}
