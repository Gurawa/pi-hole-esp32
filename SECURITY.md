# Security Considerations

## ESP32 Pi-hole Security Notes

This ESP32 implementation is designed for home networks and learning purposes. Please be aware of the following security considerations:

### Network Security

**⚠️ No Authentication**
- The web interface currently has **NO authentication**
- Anyone on your network can access and modify settings
- **Recommendation**: Use this only on trusted home networks
- Future versions will include password protection

**⚠️ HTTP Only**
- Web interface uses unencrypted HTTP
- No HTTPS/TLS support (ESP32 resource limitation)
- **Risk**: Traffic can be intercepted on local network
- **Mitigation**: Use only on trusted networks

**⚠️ DNS Port Exposure**
- Port 53 (DNS) is open by default
- Required for DNS functionality
- **Recommendation**: Use firewall to limit access if needed

### Configuration Security

**⚠️ WiFi Credentials in Code**
- WiFi password stored in `config.h` as plain text
- **IMPORTANT**: Never commit actual credentials to Git
- Use `config.h.example` as template
- Add `config.h` to `.gitignore` if needed

**⚠️ Default Settings**
- Default upstream DNS is Google (8.8.8.8)
- Consider privacy implications
- Alternative: Use Cloudflare (1.1.1.1) or Quad9 (9.9.9.9)

### Input Validation

**✅ Domain Validation**
- Domain names are validated before adding to blocklist
- Checks for valid characters and length
- XSS protection in web interface

**✅ Buffer Overflow Protection**
- DNS packet parsing includes bounds checking
- Buffer size limits enforced

### Recommendations

#### For Home Use
1. **Change default settings** in `config.h`
2. **Use strong WiFi password**
3. **Update regularly** when new versions are released
4. **Monitor your network** for unexpected behavior
5. **Keep ESP32 firmware updated**

#### For Production/Public Use
⚠️ **This implementation is NOT recommended for:**
- Public networks
- Enterprise environments
- Internet-facing deployments
- Networks with untrusted users

Use the official Pi-hole on Linux for production environments.

### Reporting Security Issues

If you discover a security vulnerability:
1. **DO NOT** create a public GitHub issue
2. Contact the repository maintainer privately
3. Allow time for a fix before public disclosure

### Future Security Enhancements

Planned for future versions:
- [ ] Web interface authentication
- [ ] HTTPS support (if ESP32 resources permit)
- [ ] Rate limiting for DNS queries
- [ ] Access control lists
- [ ] Encrypted credential storage

### Comparison with Original Pi-hole

| Security Feature | Original Pi-hole | ESP32 Pi-hole |
|------------------|------------------|---------------|
| Web Authentication | ✅ Yes | ❌ No (planned) |
| HTTPS Support | ✅ Yes | ❌ No |
| DNS over HTTPS | ✅ Yes | ❌ No |
| DNSSEC | ✅ Yes | ❌ No |
| Access Controls | ✅ Advanced | ❌ Basic |
| Audit Logging | ✅ Yes | ⚠️ Limited |

### Disclaimer

This software is provided "as is" without warranty. Use at your own risk. The developers are not responsible for any security issues or damages resulting from the use of this software.

For maximum security, use the official Pi-hole implementation on properly secured Linux hardware.
