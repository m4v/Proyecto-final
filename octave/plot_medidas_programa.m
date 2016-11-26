% script para graficar las capturas y ver rápidamente que es que

% ensayos del programa

[files] = dir("../mediciones/captura_programa_*.csv");

for i=1:length(files)
  name = files(i).name
  D = csvread(fullfile("..", "mediciones", name));
  try
    t = D(:,1) - D(1,1);
    T = D(:,2);
    ref = D(:,5);
    ref_c = D(:,9);
    piy = D(:,7);
    dc = D(:,8);
  catch
    disp("errro")
    continue
  end

  figure(1);
  plot(t, T, '-b', t, ref, '--r', t, ref_c, '-r');
  title(strrep(name, "_", " "))
  figure(2);
  plot(t, piy, 'r', t, dc, 'b');
  title(strrep(name, "_", " "))
  waitforbuttonpress()
end
