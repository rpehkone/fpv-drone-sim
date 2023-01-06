class	drone_fpv_controller {
	private:
		vec3 pos;
		quat rot;
		vec3 velocity;
		float weight;
		float power;

		static void	controller_deadzone(vec2& v, float min)
		{
			float len = vec2_length(v);
			if (len < min)
				v = (vec2){0, 0};
		}

		static quat	drone_input_controller(t_game_controller& con)
		{
			quat wishrot = QUAT_IDENTITY;

			controller_deadzone(con.joy_left, 0.05);
			controller_deadzone(con.joy_right, 0.05);
			float sens = 2;
			quat_mul_this(wishrot, quat_from_x(con.joy_right.y * sens));
			quat_mul_this(wishrot, quat_from_z(con.joy_right.x * sens));
			quat_mul_this(wishrot, quat_from_y(-1.0 * con.joy_left.x * sens));
			return (wishrot);
		}
	public:
		void	tick(t_input& input, float delta_time)
		{
			quat wishrot = QUAT_IDENTITY;

			t_game_controller con = input.controller[0];
			quat_mul_this(wishrot, drone_input_controller(con));
			// add angular velocity
			rot = slerp(rot, quat_mul(rot, wishrot), delta_time);
			quat_normalize(drone.rot);

			if (con.joy_left.y > 0)
			{
				vec3 up = quat_get_up(drone.rot);
				vec_mul(up, drone.power * con.joy_left.y);
				vec_add_this(drone.velocity, vec_mul_copy(up, delta_time));
			}

			vec3 gravity = (vec3){0, -1.8, 0};
			vec_mul(gravity, weight);
			vec_add_this(velocity, vec_mul_copy(gravity, delta_time));
			vec_add_this(pos, vec_mul_copy(velocity, delta_time));
		}

		//good value   power = 25    weight = 8
		drone_fpv_controller(float power, float weight)
		{
			rot = QUAT_IDENTITY;
			power = power;
			weight = weight;
		}
};
