from django.conf.urls.defaults import *

urlpatterns = patterns('web.home.views',
    (r'^register/$', 'register'),
    (r'^logout/$', 'logout'),
    (r'^login/$', 'login'),
    (r'^$', 'home'),
)
