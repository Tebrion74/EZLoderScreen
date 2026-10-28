// EZ Flip Vehicle: hold F (interact) next to an overturned, empty, engine-off vehicle to set it back on its wheels.
// Server-authoritative: conditions re-checked on server; only the server moves the vehicle.
// Works for anything derived from CarScript (vanilla, CarPack, Expansion cars/helis built on CarScript).
class EZFlip
{
	static const float TIME = 6.0;        // seconds of interaction
	static const float MAX_UP_Y = 0.6;    // vehicle "up" vector Y below this = overturned (~53 deg+)
	static const float MAX_SPEED = 1.0;   // m/s
	static const float LIFT = 1.0;        // metres lifted before dropping on wheels

	static CarScript GetCar(ActionTarget target)
	{
		if (!target)
			return null;
		CarScript car = CarScript.Cast(target.GetObject());
		if (!car)
			car = CarScript.Cast(target.GetParent());
		return car;
	}

	static bool CanFlip(PlayerBase player, CarScript car)
	{
		if (!player || !car || player.IsInVehicle())
			return false;
		if (car.IsDamageDestroyed())
			return false;
		if (car.EngineIsOn())
			return false;
		for (int i = 0; i < car.CrewSize(); i++)
		{
			if (car.CrewMember(i))
				return false;
		}
		if (GetVelocity(car).Length() > MAX_SPEED)
			return false;
		vector up = car.GetDirectionUp();
		return up[1] < MAX_UP_Y;
	}

	static void DoFlip(CarScript car)
	{
		vector pos = car.GetPosition();
		vector ori = car.GetOrientation(); // yaw, pitch, roll
		float surfY = GetGame().SurfaceY(pos[0], pos[2]);
		pos[1] = Math.Max(pos[1], surfY) + LIFT;
		car.SetPosition(pos);
		car.SetOrientation(Vector(ori[0], 0, 0));
		SetVelocity(car, vector.Zero);
		dBodySetAngularVelocity(car, vector.Zero);
		dBodyActive(car, ActiveState.ACTIVE);
		car.SetSynchDirty();
	}
}

const int EZ_RPC_FLIP_REQUEST = 82341004; // client -> server Param1<Object> (keybind flip)
const int EZ_RPC_CLIENT_PREFS = 82341005; // client -> server Param1<bool>  (sticky gag messages on/off)

// Keybind flip (default F6): server re-validates, flips after KEY_DELAY seconds if still valid.
modded class PlayerBase
{
	float m_EZLastFlipReq;
	bool m_EZGagMsgs = true;
	static const int EZ_FLIP_KEY_DELAY_MS = 4000;
	static const float EZ_FLIP_COOLDOWN = 10;

	void EZ_FlipKeyFinish(CarScript car)
	{
		if (!car || !IsAlive() || vector.Distance(car.GetPosition(), GetPosition()) > 6)
			return;
		if (!EZFlip.CanFlip(this, car))
		{
			NotificationSystem.SendNotificationToPlayerExtended(this, 4, "Flip vehicle", "Flip cancelled (vehicle occupied, running or moving).", "set:dayz_gui image:icon_info");
			return;
		}
		EZFlip.DoFlip(car);
	}

	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		super.OnRPC(sender, rpc_type, ctx);
		if (!GetGame().IsServer() || !sender || !GetIdentity() || sender.GetPlainId() != GetIdentity().GetPlainId())
			return;
		if (rpc_type == EZ_RPC_CLIENT_PREFS)
		{
			Param1<bool> pp = new Param1<bool>(true);
			if (ctx.Read(pp))
				m_EZGagMsgs = pp.param1;
		}
		else if (rpc_type == EZ_RPC_FLIP_REQUEST)
		{
			Param1<Object> pf = new Param1<Object>(null);
			if (!ctx.Read(pf))
				return;
			CarScript car = CarScript.Cast(pf.param1);
			float now = GetGame().GetTickTime();
			if (!car || now - m_EZLastFlipReq < EZ_FLIP_COOLDOWN)
				return;
			if (vector.Distance(car.GetPosition(), GetPosition()) > 5 || !EZFlip.CanFlip(this, car))
				return;
			m_EZLastFlipReq = now;
			NotificationSystem.SendNotificationToPlayerExtended(this, 4, "Flip vehicle", "Stand clear - flipping in 4 seconds...", "set:dayz_gui image:icon_info");
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(EZ_FlipKeyFinish, EZ_FLIP_KEY_DELAY_MS, false, car);
		}
	}
}

class ActionEZFlipVehicleCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(EZFlip.TIME);
	}
}

class ActionEZFlipVehicle : ActionContinuousBase
{
	void ActionEZFlipVehicle()
	{
		m_CallbackClass = ActionEZFlipVehicleCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_Text = "Flip vehicle";
	}

	override void CreateConditionComponents()
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTObject(UAMaxDistances.DEFAULT);
	}

	override typename GetInputType()
	{
		return ContinuousInteractActionInput;
	}

	override bool HasTarget()
	{
		return true;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return EZFlip.CanFlip(player, EZFlip.GetCar(target));
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		CarScript car = EZFlip.GetCar(action_data.m_Target);
		if (!EZFlip.CanFlip(action_data.m_Player, car))
			return;

		EZFlip.DoFlip(car);
	}
}

modded class ActionConstructor
{
	override void RegisterActions(TTypenameArray actions)
	{
		super.RegisterActions(actions);
		actions.Insert(ActionEZFlipVehicle);
	}
}

modded class CarScript
{
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionEZFlipVehicle);
	}
}
