class	drone_fpv_controller {
	private:
		vec3 pos;
		quat rot;
		float rotation_speed;
		quat angular_vel;
		float angular_damp;
		vec3 velocity;
		float weight;
		float power;

		static void	controller_deadzone(vec2& v, float min)
		{
			float len = vec2::length(v);
			if (len < min)
				v = (vec2){0, 0};
		}

		static quat	drone_input_controller(t_game_controller& con)
		{
			quat wishrot;

			controller_deadzone(con.joy_left, 0.05);
			controller_deadzone(con.joy_right, 0.05);
			float sens = M_PI_2;
			wishrot = quat::from_x(con.joy_right.y * sens));
			wishrot *= quat::from_z(con.joy_right.x * sens));
			wishrot *= quat::from_y(-1.0 * con.joy_left.x * sens));
			return (wishrot);
		}
	public:
		void	tick(t_input& input, float delta_time)
		{
			t_game_controller con = input.controller[0];
			quat wishrot = drone_input_controller(con);
			angular_vel = quat::lerp(angular_vel, QUAT_IDENTITY, delta_time * angular_damp);
			quat::normalize(angular_vel);
			angular_vel *= quat::lerp(QUAT_IDENTITY, wishrot, delta_time * rotation_speed);
			quat::normalize(angular_vel);
			rot = quat::lerp(rot, rot * angular_vel, delta_time);
			quat::normalize(rot);

			if (con.joy_left.y > 0)
			{
				vec3 up = quat::get_up(rot);
				up *= power * con.joy_left.y;
				velocity += up * delta_time;
			}

			vec3 gravity = (vec3){0, -1.8, 0};
			gravity *= weight;
			velocity += gravity * delta_time;
			pos += velocity * delta_time;
		}

		//good value   power = 25    weight = 8
		drone_fpv_controller(float power, float weight)
		{
			rot = QUAT_IDENTITY;
			rotation_speed = 6.0;
			angular_vel = QUAT_IDENTITY;
			angular_damp = 4.0;
			power = power;
			weight = weight;
		}
};
