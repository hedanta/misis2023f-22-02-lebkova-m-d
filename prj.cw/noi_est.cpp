#include <iostream>
#include <opencv2/opencv.hpp>

cv::Mat mat2gray(const cv::Mat& image) {
  cv::Mat dst = image.clone();
  normalize(image, dst, 0.0, 1.0, cv::NORM_MINMAX);
  return dst;
}

cv::Mat CreateNoiseMap(const cv::Mat& image) {
  cv::Mat noisy_image32f;
  image.convertTo(noisy_image32f, CV_32FC1);

  cv::Mat blurred_img;
  cv::blur(noisy_image32f, blurred_img, cv::Size(3, 3));

  cv::Mat blurred_img_2;
  cv::blur(noisy_image32f.mul(noisy_image32f), blurred_img_2, cv::Size(2, 2));

  cv::Mat sigma;
  cv::sqrt(cv::abs(blurred_img_2 - blurred_img.mul(blurred_img)), sigma);

  /*cv::Mat tmp;
  dst.convertTo(tmp, CV_8U, 255.0, 0.0);

  cv::Mat noise_map;
  cv::applyColorMap(tmp, noise_map, cv::COLORMAP_AUTUMN);

  return noise_map;*/

  return sigma;
}

cv::Mat AddRandomNoise(cv::Mat image, int noise_intensity) {
  cv::Mat noise(image.size(), image.type());
  cv::randu(noise, cv::Scalar(-noise_intensity), cv::Scalar(noise_intensity));

  image += noise;
  return image;
}

cv::Mat GetRoundRoi(const cv::Mat& image) {
  cv::Mat out_circle = cv::Mat::zeros(image.size(), image.type());
  cv::Mat in_circle = cv::Mat::zeros(image.size(), image.type());
  cv::Mat mask = cv::Mat::zeros(image.size(), image.type());

  cv::Mat roi_img = cv::Mat::zeros(image.size(), image.type());

  cv::circle(out_circle, cv::Point(mask.cols / 2, mask.rows / 2), 300, (255, 255, 255), -1);
  cv::circle(in_circle, cv::Point(mask.cols / 2, mask.rows / 2), 100, (255, 255, 255), -1);

  cv::subtract(out_circle, in_circle, mask);

  image.copyTo(roi_img, mask);

  return roi_img;
}

std::vector<cv::Mat> CreateEnsemble(const cv::Mat& image, const int& amount) {
  std::vector<cv::Mat> noisy_images;

  double intense = 200.0;

  for (int i = 0; i < amount; i += 1) {
    cv::Mat noisy_image = cv::Mat::zeros(image.size(), CV_32FC1);
    image.copyTo(noisy_image);
    
    noisy_image = AddRandomNoise(noisy_image, intense);
    noisy_images.push_back(noisy_image);
  }

  return noisy_images;
};

cv::Mat GetEnsembleMean(const cv::Mat& image, const std::vector<cv::Mat> ensemble, const int& amount) {
  cv::Mat ensemble_sum = cv::Mat::zeros(image.size(), CV_32FC1);
  cv::Mat ensemble_mean = cv::Mat::zeros(image.size(), CV_32FC1);

  for (int i = 1; i < amount; i += 1) {
    cv::Mat img_32f;
    ensemble[i].convertTo(img_32f, CV_32FC1);
    ensemble_sum += img_32f;
  }

  ensemble_mean = ensemble_sum.clone();

  ensemble_mean /= (amount - 1);

  return ensemble_mean;
}

cv::Mat GetImageNoise(const cv::Mat& image, const cv::Mat& ensemble_mean) {
  cv::Mat noise = cv::Mat::zeros(image.size(), CV_32FC1);
  cv::subtract(image, ensemble_mean, noise);
  return noise;
}

void GetNoiseHist(const cv::Mat& image) {
  int hist_size = 256;
  float range[] = { 0.0f, 1.0f + FLT_EPSILON};
  const float* hist_range = { range };

  cv::Mat hist;
  cv::calcHist(&image, 1, 0, cv::Mat(), hist, 1, &hist_size, &hist_range);

  int hist_w = 500; 
  int hist_h = 200;
  int bin_w = cvRound((double)hist_w / hist_size);

  cv::Mat hist_img(hist_h, hist_w, CV_8U, cv::Scalar(0, 0, 0));

  normalize(hist, hist, 0, hist_img.rows, cv::NORM_MINMAX);

  for (int i = 1; i < hist_size; i += 1) {
    cv::line(hist_img, cv::Point(bin_w * (i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
      cv::Point(bin_w * (i), hist_h - cvRound(hist.at<float>(i))),
      cv::Scalar(255, 0, 0), 2, 8, 0);
  }
  cv::imshow("hist", hist_img);
}

int main() {
  cv::Mat image = cv::imread("cat.jpg", cv::IMREAD_GRAYSCALE);
  cv::Mat image_32f = cv::Mat::zeros(image.size(), CV_32FC1);
  image.convertTo(image_32f, CV_32FC1);

  cv::Mat noise_map = CreateNoiseMap(image_32f);

  const int amount = 51;
  std::vector<cv::Mat> ensemble = std::move(CreateEnsemble(image_32f, amount));
  image_32f = ensemble[0];

  cv::Mat ens_mean = GetEnsembleMean(image_32f, ensemble, amount);

  cv::Mat noise = GetImageNoise(image_32f, ens_mean);

  cv::imshow("img", mat2gray(image_32f));
  cv::imshow("mean", mat2gray(ens_mean));
  //cv::imshow("noise", mat2gray(noise));
  cv::Mat noise_n = cv::Mat::zeros(image_32f.size(), CV_8U);
  noise.convertTo(noise_n, CV_8U);
  cv::imshow("noise", noise_n);

  GetNoiseHist(noise_map);

  /*
  cv::cvtColor(noise_map, noise_map, cv::COLOR_RGB2GRAY, 1);

  cv::Mat thresh_mask_low;
  cv::threshold(noise_map, thresh_mask_low, 64, 255, 1);

  cv::Mat thresh_mask_high;
  cv::threshold(noise_map, thresh_mask_high, 64, 255, 0);

  cv::Mat roi = GetRoundRoi(noise);

  cv::Mat n_low = cv::Mat::zeros(image.size(), CV_32F);
  cv::multiply(roi, thresh_mask_low, n_low);
  cv::imshow("N' low", n_low);


  cv::Mat n_high = cv::Mat::zeros(image.size(), CV_32F);
  cv::multiply(roi, thresh_mask_high, n_high);
  cv::imshow("N' high", n_high);
  */

  cv::waitKey(0);

  cv::destroyAllWindows();
}
