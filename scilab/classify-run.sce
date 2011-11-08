// Para rodar:
// - primeiro ponha o caminho pra base de dados em mypath abaixo
// - execute este script no scilab
// - precisa do SIP
//
// Talvez voce queira a saida num arquivo, neste caso entre no scilab assim:
//
// scilab -nw | tee saida.txt
//
mode(-1);
lines(0); // no vertical paging
stacksize(20000000);
sip_quiet;
//sip_wordy;

// se quiser, insira o caminho pras imagens aqui
//mypath="/home/rfabbri/lib/pics/test-imgs/color-webcam-db/lenovo/easy/";
mypath="/home/rfabbri/lib/pics/test-imgs/color-webcam-db/lenovo/";

//mypath="./"

method = 'hsv_sip';
//method = 'distance_to_reference'


// precomputed medians
has_medians=%t;
fmedians=mypath + 'medians.dat';
if has_medians
  load(fmedians,'medians');
end

fs = ls(mypath+'*.jpg');

acertos=0;
acertos_com_certeza=0;
num_certain = 0;

nimgs = size(fs,1);


classes = [];
true_classes = [];
certainties = [];
secondary_classes = [];
for i=1:nimgs
  disp ('classifying' + fs(i));
  true_class=unix_g('echo ' + basename(fs(i)) + '|grep -o ^[^\/-]*-|grep -o [^-]*');
  true_classes(i) = true_class;


  if has_medians
    medians(i,:)
    [class, certainty, confidence, secondary_class] =...
      color_classify_single_c(medians(i,:),method);
  else
    im = imread(fs(i));
    [class, certainty, confidence, secondary_class] =...
      color_classify(im,method);
  end



  certainties(i) = certainty;

  classes(i) = class;

  secondary_classes(i) = secondary_class;

  if certainty ~= 'certain'
    warning('guessing');
  else
    num_certain = num_certain + 1;
  end

  disp('true class: ' + true_class + ', result: ' + class);
  if class == true_class
    acertos = acertos + 1;
    if certainty == 'certain'
      acertos_com_certeza = acertos_com_certeza + 1;
    end
  else
    disp('Classification error.');
  end
end

disp ('==============================');
disp ('Taxa de acerto: ' + string(acertos/nimgs) + ' (' + string(acertos) + '/' + string(nimgs) + ')'); 
disp ('Taxa de acerto com certeza: ' + string(acertos_com_certeza/num_certain) ..
   + ' (' + string(acertos_com_certeza) + '/' + string(num_certain) + ')' + ..
   ' coverage: ' + string(num_certain/nimgs)' +' (' + string(num_certain) + '/' + string(nimgs) + ')');
// disp ('Red TP, FP, FN: ', );

tf=(true_classes==classes);
ei=find(tf == %f)';
disp 'Mistakes:';
disp 'ground truth | detected | secondary detected | certainty | file | id';
res=[true_classes(ei),classes(ei),secondary_classes(ei),certainties(ei),basename(fs(ei)), string(ei)]
