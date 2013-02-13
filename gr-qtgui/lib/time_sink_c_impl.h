/* -*- c++ -*- */
/*
 * Copyright 2011,2012 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_QTGUI_TIME_SINK_C_IMPL_H
#define INCLUDED_QTGUI_TIME_SINK_C_IMPL_H

#include <qtgui/time_sink_c.h>
#include <timedisplayform.h>
#include <gruel/thread.h>
#include <gruel/high_res_timer.h>

namespace gr {
  namespace qtgui {
    
    class QTGUI_API time_sink_c_impl : public time_sink_c
    {
    private:
      void initialize();

      gruel::mutex d_mutex;

      int d_size;
      double d_samp_rate;
      std::string d_name;
      int d_nconnections;

      int d_index;
      std::vector<double*> d_residbufs;

      QWidget *d_parent;
      TimeDisplayForm *d_main_gui;

      gruel::high_res_timer_type d_update_time;
      gruel::high_res_timer_type d_last_time;

      void npoints_resize();

    public:
      time_sink_c_impl(int size, double samp_rate,
		       const std::string &name,
		       int nconnections,
		       QWidget *parent=NULL);
      ~time_sink_c_impl();

      bool check_topology(int ninputs, int noutputs);

      void exec_();
      QWidget*  qwidget();
      PyObject* pyqwidget();

      void set_y_axis(double min, double max);
      void set_update_time(double t);
      void set_title(const std::string &title);
      void set_line_label(int which, const std::string &label);
      void set_line_color(int which, const std::string &color);
      void set_line_width(int which, int width);
      void set_line_style(int which, int style);
      void set_line_marker(int which, int marker);
      void set_nsamps(const int size);
      void set_samp_rate(const double samp_rate);
      void set_line_alpha(int which, double alpha);

      std::string title();
      std::string line_label(int which);
      std::string line_color(int which);
      int line_width(int which);
      int line_style(int which);
      int line_marker(int which);
      double line_alpha(int which);

      void set_size(int width, int height);
      
      int nsamps() const;

      void enable_menu(bool en);
      void enable_grid(bool en);
      void enable_autoscale(bool en);
      void toggle_stem_plot();
      void reset();

      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
    };

  } /* namespace qtgui */
} /* namespace gr */

#endif /* INCLUDED_QTGUI_TIME_SINK_C_IMPL_H */