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
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventStartedMoving& e) { std::cout << "Moving" << std::endl; return RunningState{}; }
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventStartedShooting& e) { std::cout << "Shooting" << std::endl; return ShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(RunningState& s, const EventStoppedMoving& e) { std::cout << "Stopped Moving" << std::endl; return IdleState{}; }
	std::optional<PlayerAnimVar> On_Event(ShootingState& s, const EventStoppedShooting& e) { std::cout << "Stopped Shooting" << std::endl; return IdleState{}; }
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventBeganJump& e) { std::cout << "Jumping" << std::endl; return InAirState{}; }
	std::optional<PlayerAnimVar> On_Event(RunningState& s, const EventBeganJump& e) { std::cout << "Jumping" << std::endl; return InAirState{}; }
	std::optional<PlayerAnimVar> On_Event(ShootingState& s, const EventBeganJump& e) { std::cout << "Jumping" << std::endl; return InAirState{}; }
	std::optional<PlayerAnimVar> On_Event(InAirState& s, const EventLanding& e) { std::cout << "Landing" << std::endl; if (e.moving) { return RunningState{}; } else { return IdleState{}; } }


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
		if (std::holds_alternative<IdleState>(state_)) { return "Idle"; }
		else if (std::holds_alternative<ShootingState>(state_)) { return "Shoot"; }
		else if (std::holds_alternative<RunningState>(state_)) { return "Walk"; }
		else if (std::holds_alternative<InAirState>(state_)) { return "Jump"; }
		else { return "NoStateCurrentlyHeld"; }
	}
};

#endif