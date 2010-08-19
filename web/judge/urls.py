from django.conf.urls.defaults import *

urlpatterns = patterns('web.judge.views',
    (r'^manage/$', 'manage'),
    (r'^standings/$', 'standings'),
    (r'^results/$', 'results'),
)
