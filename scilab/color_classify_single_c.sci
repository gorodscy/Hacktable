function [label, certainty_level, confidence, secondary_label] = color_classify_single_c(RGB, method)
  method = 'hsv_sip';

  RGB = string(RGB);
  result = unix_g('color_classify_cmd ' + RGB(1) + ' ' + RGB(2) + ' ' + RGB(3));

  result = strsplit(result, ' ');
  label = result(1);
  secondary_label = result(2);
  certainty_level = result(3);

  confidence = -1.0;

endfunction
