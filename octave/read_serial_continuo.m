% Script de Octave para leer y graficar datos desde el puerto serial.

serial_init

% creamos nuestras figuras
clf
subplot(2, 1, 1);
h11 = plot(1, 1, '-b;temperatura;');
legend('location', 'northwest');
hold on
h12 = plot(1, 1, '--r;referencia;');
h13 = plot(1, 1, '-r;referencia cond;');
grid on
subplot(2, 1, 2);
h21 = plot(1, 1, '-r;salida PI;');
legend('location', 'northwest');
hold on
h22 = plot(1, 1, '-b;salida PI (saturacin);');
grid on

log = fopen("registro.log", "a");
fwrite(log, sprintf("-Inicio del registro de captura %s\r\n", fecha()));

%srl_write(fd, sprintf("S%d\n", referencia)); % valor del escalon
srl_write(fd, "c"); % iniciar captura
Tm = 1; % en este modo el muestreo es cada seg
if (exist("i", "var"))
  i = length(t);
 else
  i = 1;
end
%clear t temp ref piy piys dc
more off
unwind_protect
  while(1)
    % leemos una línea
    str = read_linea(fd);
    try
      [n, T, Tth, Tlm, ADth, ADlm, DC, REF, REF_C, PIx, PIy ] = strread(str, 
            "%f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f");
    catch
      % desactivo el warning que es molesto
      [text, id] = lastwarn();
      warning("off", id);
      printf(str)
      continue
    end
    t(i) = n * Tm;
    temp(i) = T;
    tempth(i) = Tth;
    templm(i) = Tlm;
    ref(i) = REF;
    ref_c(i) = REF_C;
    dc(i) = DC*100;
    piy(i) = PIy;
    piys(i) = DC*100;
    pix(i) = PIx;
    % actualizar gráfico
    set(h11, 'XData', t, 'YData', temp);
    set(h12, 'XData', t, 'YData', ref);
    set(h13, 'XData', t, 'YData', ref_c);
    set(h21, 'XData', t, 'YData', piy);
    set(h22, 'XData', t, 'YData', piys);
    drawnow;
    %guardamos un registro
    fwrite(log, str);
    i++;
    % hacemos una pausa proporcional al muestreo así no estamos esperando mucho 
    % en srl_read que dificulta terminar el script con ctrl-c
    pause(Tm*0.8);
  end
unwind_protect_cleanup
  % Ctrl-C, detener y cerrar la conección
  srl_write(fd, "c");
  fclose(fd);
  fwrite(log, sprintf("-Fin de la captura %s\r\n", fecha()));
  fclose(log);
  % guardar los datos capturados
  % antes de guardar las longitudes tienen que ser iguales
  N = length(pix);
  t = t(1:N);
  temp = temp(1:N);
  piy = piy(1:N);
  ref = ref(1:N);
  ref_c = ref_c(1:N);
  pix = pix(1:N);
  dc = dc(1:N);
  templm = templm(1:N);
  tempth = tempth(1:N);
  csvwrite(sprintf("captura_continua_%s.csv", fecha()),
      [t' temp' tempth' templm' ref' pix' piy' dc' ref_c']);
  printf("captura guardada\n")
end
