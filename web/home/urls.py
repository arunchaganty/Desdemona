from django.conf.urls.defaults import *

# Uncomment the next two lines to enable the admin:
# from django.contrib import admin
# admin.autodiscover()

urlpatterns = patterns('web.home.views',
    (r'^register/$', 'register'),
    (r'^logout/$', 'logout'),
    (r'^$', 'home'),
)
