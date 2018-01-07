% initialize everything
System;
AMAX12_p75W_SB;
motor_1 = MotorParam;
AMAX16_2W_SB;
motor_2 = MotorParam;
AMAX19_2p5W_SB;
motor_3 = MotorParam;
AMAX22_5W_SB;
motor_4 = MotorParam;
AMAX22_6W_SB;
motor_5 = MotorParam;

% Graph params
graph_rows = 1;
graph_cols = 3;

% Find the best motor for q1
motors_param = [motor_1 motor_2 motor_3 motor_4 motor_5];

% Name motors
motors_name = categorical({'AMAX12 p75W', 'AMAX16 2W',...
    'AMAX19 2p5W', 'AMAX22 5W SB', 'AMAX22 6W SB'
});

% Use loop to find the step response for each motor for q1
% Fix q0 to the default motor
q0 = motor_4 .* motor_param_unit_convert;

% Try each motor
riseTimes = zeros(1, 5);
settleTimes = zeros(1, 5);
overshoots = zeros(1, 5);
for i = 1:size(motors_param, 2)
    q1 = motors_param(1:end, i) .* motor_param_unit_convert;
    SystemHeadless;

    % Compare system step responses of q0
    stepRes = stepinfo(ol_q0);

    % Record values
    riseTimes(i) = stepRes.RiseTime;
    settleTimes(i) = stepRes.SettlingTime;
    overshoots(i) = stepRes.Overshoot;
end

% Compare these motors at large
figure(1);
subplot(graph_rows, graph_cols, 1);
bar(motors_name, riseTimes);
title('Rise time');
subplot(graph_rows, graph_cols, 2);
bar(motors_name, settleTimes);
title('Settle time');
subplot(graph_rows, graph_cols, 3);
bar(motors_name, overshoots);
title('Overshoot');
ylim([0, 100]);

% Now assigning motor 1 to be the best motor from previous experiment
q1 = motors_param(1:end, 1) .* motor_param_unit_convert;

% Try each motor for q0 to see which one performs better
for i = 1:size(motors_param, 2)
    q0 = motors_param(1:end, i) .* motor_param_unit_convert;
    SystemHeadless;

    % Get and record step response
    stepRes = stepinfo(ol_q0);
    riseTimes(i) = stepRes.RiseTime;
    settleTimes(i) = stepRes.SettlingTime;
    overshoots(i) = stepRes.Overshoot;
end

% Plot the performance for Q0
figure(2);
subplot(graph_rows, graph_cols, 1);
bar(motors_name, riseTimes);
title('Rise time');
subplot(graph_rows, graph_cols, 2);
bar(motors_name, settleTimes);
title('Settle time');
subplot(graph_rows, graph_cols, 3);
bar(motors_name, overshoots);
title('Overshoot');
ylim([0, 100]);

% =====================[After choosing best motors]========================
q0 = motors_param(1:end, 5) .* motor_param_unit_convert;
q1 = motors_param(1:end, 1) .* motor_param_unit_convert;

figure(3);
subplot(2, 1, 1);
step(ol_q0);
title('Q0 open loop step response');
subplot(2, 1, 2);
step(ol_q1);
title('Q1 open loop step response');