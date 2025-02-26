#pragma once
#include <FSM/IgnoreUnknownEvent.h>
#include <variant>
#include <FSM/Events.h>

struct IdleState { };
struct RunningState {};
struct InAirState {};
struct ShootingState {};
struct InAirShootingState {};
struct RunningAndShootingState {};

using PlayerAnimVar = std::variant<IdleState, RunningState,InAirState,ShootingState,InAirShootingState,RunningAndShootingState>;


