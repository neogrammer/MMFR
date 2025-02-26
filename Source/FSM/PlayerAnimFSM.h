#ifndef PLAYERANIMFSM_H__
#define PLAYERANIMFSM_H__
#include <FSM/DuckFold.h>
#include <optional>
#include <iostream>
#include <type_traits>
#include <variant>

class FSM_Player : public FSM<FSM_Player, PlayerAnimVar>
{
public:
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventStartedMoving& e)	{	return RunningState{}; 	}
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventStartedShooting& e) { return ShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(RunningState& s, const EventStoppedMoving& e) { return IdleState{}; }
	std::optional<PlayerAnimVar> On_Event(ShootingState& s, const EventStoppedShooting& e) { return IdleState{}; }


	/*std::optional<PlayerAnimVar> On_Event(InAirState& s, const EventLanded& e)
	{
		if (e.isMoving)
			return RunningState{};
		else
			return IdleState{};
	}*/
	template <typename State, typename Event>
	std::optional<PlayerAnimVar> On_Event(State&, const Event&) { 	return std::nullopt; 	}
	std::string getStateName()
	{
		if (std::holds_alternative<IdleState>(state_)) { return "IdleState"; }
		else if (std::holds_alternative<ShootingState>(state_)) { return "ShootingState"; }
		else if (std::holds_alternative<RunningState>(state_)) { return "RunningState"; }
		else { return "NoStateCurrentlyHeld"; }
	}
};

#endif