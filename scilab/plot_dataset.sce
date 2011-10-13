// se quiser, insira o caminho pras imagens aqui
mypath="/home/rfabbri/lib/pics/test-imgs/color-webcam-db/lenovo/";

// precomputed medians
has_medians=%t;
fmedians=mypath + 'medians.dat';
if has_medians
  load(fmedians,'medians');
end


clf;
param3d1(medians(:,1), medians(:,2), medians(:,3));
e = gce();
e.line_mode = "off";
e.mark_mode = "on";
