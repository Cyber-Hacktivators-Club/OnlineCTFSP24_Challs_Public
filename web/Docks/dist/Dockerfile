FROM nibrev/php-5.3-apache

# Enable mod_rewrite and install necessary extensions
RUN docker-php-ext-install mysqli pdo pdo_mysql && \
    a2enmod rewrite

# Set ServerName to avoid warnings
RUN echo "ServerName localhost" >> /etc/apache2/apache2.conf

# Set working directory
WORKDIR /var/www/html

# Copy PHP file to the container
COPY vuln.php /var/www/html/vuln.php

# Expose port 80
EXPOSE 80

# Start Apache server
CMD ["apache2-foreground"]
