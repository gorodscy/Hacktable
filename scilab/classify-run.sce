// Para rodar:
// - primeiro entre no diretorio da base de dados
// - execute este script no scilab
//
// Talvez voce queira a saida num arquivo, neste caso entre no scilab assim:
//
// scilab -nw | tee saida.txt
//
stacksize(20000000);
sip_quiet;

fs = ls('*.jpg');

for i=1:size(fs,1)
  disp ('classificando ' + fs(i));
  im = imread(fs(i));
  exec /home/rfabbri/pictures/test-imgs/color-webcam-db/classify.sce;
end
